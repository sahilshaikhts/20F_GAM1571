//
// Copyright (c) 2016-2020 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "FrameworkPCH.h"

#include "FWCore.h"
#include "GL/GLExtensions.h"
#include "GL/WGLExtensions.h"
#include "GL/MyGLContext.h"
#include "GameCore.h"
#include "Utility/Helpers.h"
#include"EventSystem/EventManager.h"
#include"EventSystem/Event.h"

namespace fw {

// Initialize opengl window on windows, huge chunks taken from nehe
//    http://nehe.gamedev.net/tutorial/creating_an_opengl_window_%28win32%29/13001/
// Update to GL 3+ using this info:
//    https://mariuszbartosik.com/opengl-4-x-initialization-in-windows-without-a-framework/

// Public methods

FWCore::FWCore()
{
    m_EscapeKeyWillQuit = true;

    m_WindowWidth = -1;
    m_WindowHeight = -1;

    m_hWnd = nullptr;
    m_hRenderingContext = nullptr;
    m_hDeviceContext = nullptr;
    m_hInstance = nullptr;
    m_pMyGLContext = nullptr;

    for( int i=0; i<256; i++ )
    {
        m_KeyStates[i] = false;
        m_OldKeyStates[i] = false;
    }

    for( int i=0; i<3; i++ )
    {
        m_MouseButtonStates[i] = false;
        m_OldMouseButtonStates[i] = false;
    }

    m_WindowIsActive = false;
    m_FullscreenMode = false;
}

FWCore::~FWCore()
{
    delete m_pMyGLContext;
}

bool FWCore::Init(int width, int height)
{
    m_WindowWidth = width;
    m_WindowHeight = height;

    // Create Our OpenGL Window.
    if( !CreateGLWindow( "OpenGL Window", width, height, 32, 0, 24, 8, 1, m_FullscreenMode ) )
    {
        PostQuitMessage( 0 );
        return false;
    }

    // Initialize OpenGL Extensions, must be done after OpenGL Context is created.
    OpenGL_InitExtensions();
    WGL_InitExtensions();

    return true;
}

int FWCore::Run(GameCore* pGame)
{
    
    // Main loop.
    MSG message;
    bool done = false;

    double previousTime = GetSystemTimeSinceGameStart();

    while( !done )
    {
        if( PeekMessage( &message, nullptr, 0, 0, PM_REMOVE ) )
        {
            if( message.message == WM_QUIT )
            {
                done = true;
            }
            else
            {
                TranslateMessage( &message );
                DispatchMessage( &message );
            }
        }
        else
        {
            double currentTime = GetSystemTimeSinceGameStart();
            double deltaTime = currentTime - previousTime;
            previousTime = currentTime;

            pGame->Update( (float)deltaTime );
            pGame->Draw();

            SwapBuffers();

            // Backup the state of the keyboard and mouse.
            for( int i=0; i<256; i++ )
                m_OldKeyStates[i] = m_KeyStates[i];

            for( int i=0; i<3; i++ )
                m_OldMouseButtonStates[i] = m_MouseButtonStates[i];
        }
    }

    // Truncate wParam in 64-bit mode to an int.
    return static_cast<int>( message.wParam );
}

void FWCore::Shutdown()
{
    KillGLWindow( true );
}

void FWCore::SetWindowSize(int width, int height)
{
    int maxWidth = GetSystemMetrics( SM_CXFULLSCREEN );
    int maxHeight = GetSystemMetrics( SM_CYFULLSCREEN );

    float aspect = static_cast<float>( width ) / height;

    if( width > maxWidth )
    {
        width = maxWidth;
        height = static_cast<int>(maxWidth / aspect);
    }

    if( height > maxHeight )
    {
        width = static_cast<int>(maxHeight * aspect);
        height = maxHeight;
    }

    DWORD dwStyle = static_cast<DWORD>( GetWindowLongPtr( m_hWnd, GWL_STYLE ) );
    DWORD dwExStyle = static_cast<DWORD>( GetWindowLongPtr( m_hWnd, GWL_EXSTYLE ) );
    HMENU menu = GetMenu( m_hWnd );

    // Calculate the full size of the window needed to match our client area of width/height.
    RECT WindowRect = { 0, 0, width, height };
    AdjustWindowRectEx( &WindowRect, dwStyle, menu ? TRUE : FALSE, dwExStyle );

    int windowWidth = WindowRect.right - WindowRect.left;
    int windowHeight = WindowRect.bottom - WindowRect.top;

    SetWindowPos( m_hWnd, 0, 0, 0, windowWidth, windowHeight, SWP_NOZORDER | SWP_NOMOVE );

    ResizeWindow( width, height );
}

bool FWCore::IsKeyDown(int value)
{
    assert( value >= 0 && value < 256 );
    return m_KeyStates[value];
}

bool FWCore::IsMouseButtonDown(int id)
{
    assert( id >= 0 && id < 3 );
    return m_MouseButtonStates[id];
}

void FWCore::GetMouseCoordinates(int* mx, int* my)
{
    POINT p;
    if( GetCursorPos( &p ) )
    {
        if( ScreenToClient( m_hWnd, &p ) )
        {
            *mx = p.x;
            *my = p.y;
        }
    }
}

void FWCore::SwapBuffers()
{
    ::SwapBuffers( m_hDeviceContext );
}

// Protected methods.

void FWCore::ResizeWindow(int width, int height)
{
    if( height <= 0 ) height = 1;
    if( width <= 0 ) width = 1;

    m_WindowWidth = width;
    m_WindowHeight = height;
}

bool FWCore::CreateGLWindow(char* title, int width, int height, unsigned char colorBits, unsigned char alphaBits, unsigned char zBits, unsigned char stencilBits, unsigned char multisampleSize, bool fullscreenflag)
{
    DWORD dwExStyle;
    DWORD dwStyle;

    RECT WindowRect;
    WindowRect.left = (long)0;
    WindowRect.right = (long)width;
    WindowRect.top = (long)0;
    WindowRect.bottom = (long)height;

    m_FullscreenMode = fullscreenflag;

    m_hInstance = GetModuleHandle( nullptr );       // Grab an instance for our window.

    // Define and register the window class.
    {
        WNDCLASSEX wc;
        ZeroMemory( &wc, sizeof(wc) );
        wc.cbSize = sizeof( wc );

        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;  // Redraw on move, and own DC for window.
        wc.lpfnWndProc = (WNDPROC)FWCore::WndProc;      // WndProc handles messages.
        wc.cbClsExtra = 0;                              // No extra window data.
        wc.cbWndExtra = 0;                              // No extra window data.
        wc.hInstance = m_hInstance;                     // Set the instance.
        wc.hIcon = LoadIcon( 0, IDI_WINLOGO );          // Load the default icon.
        wc.hCursor = LoadCursor( 0, IDC_ARROW );        // Load the arrow pointer.
        wc.hbrBackground = 0;                           // No background required.
        wc.lpszMenuName = nullptr;                      // We don't want a menu.
        wc.lpszClassName = "MyWindowClass";             // Set the class name.

        // Attempt to register the Window Class.
        if( !RegisterClassEx( &wc ) )
        {
            return FailAndCleanup( "Failed To Register The Window Class." );
        }
    }

    if( m_FullscreenMode )
    {
        DEVMODE dmScreenSettings;                                   // Device mode.
        memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) ); // Makes sure memory's cleared.
        dmScreenSettings.dmSize = sizeof( dmScreenSettings );       // Size of the devmode structure.
        dmScreenSettings.dmPelsWidth  = width;                      // Selected screen width.
        dmScreenSettings.dmPelsHeight = height;                     // Selected screen height.
        dmScreenSettings.dmBitsPerPel = colorBits;                  // Selected bits per pixel.
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Try to set selected mode and get results.  NOTE: CDS_FULLSCREEN gets rid of start bar.
        if( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
        {
            // If the mode fails, offer two options.  Quit or run in a window.
            if( MessageBox( 0, "The requested fullscreen mode is not supported by\nyour video card.\nTry a different resolution.\nUse Windowed Mode Instead?", "", MB_YESNO|MB_ICONEXCLAMATION ) == IDYES )
            {
                m_FullscreenMode = false;
            }
            else
            {
                //return FailAndCleanup( "Program Will Now Close." );
                return false;
            }
        }
    }

    if( m_FullscreenMode )
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle = WS_POPUP;
        ShowCursor( false );
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle = WS_OVERLAPPEDWINDOW;
    }

    AdjustWindowRectEx( &WindowRect, dwStyle, false, dwExStyle );   // Adjust window to true requested size.

    // Create our window.
    {
        m_hWnd = CreateWindowEx( dwExStyle,           // Extended style for the window.
                 "MyWindowClass",                     // Class name.
                 title,                               // Window title.
                 WS_CLIPSIBLINGS | WS_CLIPCHILDREN |  // Required window style.
                 dwStyle,                             // Selected window style.
                 0, 0,                                // Window position.
                 WindowRect.right-WindowRect.left,    // Calculate adjusted window width.
                 WindowRect.bottom-WindowRect.top,    // Calculate adjusted window height.
                 nullptr,                             // No parent window.
                 nullptr,                             // No menu.
                 m_hInstance,                         // Instance.
                 this );                              // Pass a pointer to this FWCore object to WM_NCCREATE.
        
        if( m_hWnd == nullptr )
        {
            return FailAndCleanup( "Window Creation Error." );
        }
    }

    // Get the device context.
    {
        m_hDeviceContext = GetDC( m_hWnd );
        if( m_hDeviceContext == nullptr )
            return FailAndCleanup( "Failed to get the device context." );
    }

    // Create an OpenGL rendering context.
    m_pMyGLContext = new MyGLContext();
    if( m_pMyGLContext->Create( m_hInstance, m_hDeviceContext, 4, 4, true, colorBits, alphaBits, zBits, stencilBits, multisampleSize ) == false )
        return FailAndCleanup( "Failed to create WGL context." );

    ShowWindow( m_hWnd, SW_SHOW );   // Show the window.
    SetForegroundWindow( m_hWnd );   // Slightly higher priority.
    SetFocus( m_hWnd );              // Sets keyboard focus to the window.
    ResizeWindow( width, height );   // Set up our screen.

    return true;
}

bool FWCore::FailAndCleanup(const char* pMessage)
{
    KillGLWindow( true );
    MessageBox( 0, pMessage, "ERROR", MB_OK|MB_ICONEXCLAMATION );
    return false;
}

void FWCore::KillGLWindow(bool destroyInstance)
{
    if( m_FullscreenMode )
    {
        ChangeDisplaySettings( nullptr, 0 );
        ShowCursor( true );
    }

    if( m_hDeviceContext && !ReleaseDC( m_hWnd, m_hDeviceContext ) )
    {
        MessageBox( 0, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
    }

    if( m_hWnd && !DestroyWindow( m_hWnd ) )
    {
        MessageBox( 0, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
    }

    if( destroyInstance && m_hInstance != nullptr )
    {
        if( !UnregisterClass( "MyWindowClass", m_hInstance ) )
        {
            MessageBox( 0, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION );
        }
        m_hInstance = 0;
    }

    m_hDeviceContext = 0;
    m_hWnd = 0;
}

// This is a static method.
LRESULT CALLBACK FWCore::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! WARNING !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! READ THIS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // This is a static method, which means it's essentially a global function.
    // It has no "this".
    // That means you can't access variables and methods directly.
    // It does know about the FWCore class though and has access to public
    //     variables and methods of any instance of the class.
    // To access the single instance of FWCore that we created
    //     you have to use the pFWCore pointer initialized just below.
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Get a pointer to the FWCore object associated with this window.
    FWCore* pFWCore = (FWCore*)GetWindowLongPtr( hWnd, GWLP_USERDATA );

    switch( uMsg )
    {
    case WM_NCCREATE:
        {
            // Set the user data for this hWnd to the FWCore* we passed in, used on first line of this method above.
            CREATESTRUCT* pCreateStruct = reinterpret_cast<CREATESTRUCT*>( lParam );
            FWCore* pFWCore = static_cast<FWCore*>( pCreateStruct->lpCreateParams );
            SetWindowLongPtr( hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>( pFWCore ) );

            if( pFWCore )
            {
                pFWCore->m_hWnd = hWnd;
            }
        }
        return 1;

    case WM_DESTROY:
        {
            if( pFWCore )
            {
                pFWCore->m_hWnd = nullptr;
            }
        }
        return 0;

    case WM_ACTIVATE:
        {
            if( !HIWORD(wParam) )
            {
                pFWCore->m_WindowIsActive = true;
            }
            else
            {
                pFWCore->m_WindowIsActive = false;
            } 
        }
        return 0;

    case WM_SYSCOMMAND:
        {
            switch( wParam )
            {
            // Don't let screensaver or monitor power save mode kick in.
            case SC_SCREENSAVE:
            case SC_MONITORPOWER:
                return 0;
            }
        }
        break;

    case WM_CLOSE:
        {
            PostQuitMessage( 0 );
        }
        return 0;

    case WM_KEYDOWN:
        {
            bool keyWasPressedLastTimeMessageArrived = lParam & (1 << 30);

            if( keyWasPressedLastTimeMessageArrived == false )
            {
                if( wParam == VK_ESCAPE && pFWCore->m_EscapeKeyWillQuit )
                    PostQuitMessage( 0 );

                pFWCore->m_KeyStates[wParam] = true;
            }
        }
        return 0;

    case WM_KEYUP:
        {
            pFWCore->m_KeyStates[wParam] = false;
        }
        return 0;

    case WM_MOUSEMOVE:
        {
            int x = GET_X_LPARAM( lParam );
            int y = GET_Y_LPARAM( lParam );
        }
        return 0;

    case WM_LBUTTONDOWN:
        {
            pFWCore->m_MouseButtonStates[0] = true;

            int x = GET_X_LPARAM( lParam );
            int y = GET_Y_LPARAM( lParam );
        }
        return 0;

    case WM_LBUTTONUP:
        {
            pFWCore->m_MouseButtonStates[0] = false;

            int x = GET_X_LPARAM( lParam );
            int y = GET_Y_LPARAM( lParam );
        }
        return 0;

    case WM_SIZE:
        {
            pFWCore->ResizeWindow( LOWORD(lParam), HIWORD(lParam) );
        }
        return 0;
    }

    // Pass all unhandled messages to DefWindowProc.
    return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

} // namespace fw
