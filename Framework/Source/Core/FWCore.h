#ifndef __FWCore_H__
#define __FWCore_H__

namespace fw {

class MyGLContext;
class GameCore;

class FWCore
{
protected:
    bool m_EscapeKeyWillQuit;

    int m_WindowWidth;
    int m_WindowHeight;

    HWND m_hWnd;
    HGLRC m_hRenderingContext;
    HDC m_hDeviceContext;
    HINSTANCE m_hInstance;
    MyGLContext* m_pMyGLContext;

    GameCore* m_pGame;

    bool m_KeyStates[256];
    bool m_MouseButtonStates[3];
    bool m_OldKeyStates[256];
    bool m_OldMouseButtonStates[3];
    bool m_WindowIsActive;
    bool m_FullscreenMode;

protected:
    void ResizeWindow(int width, int height);
    bool CreateGLWindow(char* title, int width, int height, unsigned char colorBits, unsigned char alphaBits, unsigned char zBits, unsigned char stencilBits, unsigned char multisampleSize, bool fullscreenflag);
    bool FailAndCleanup(const char* pMessage);
    void KillGLWindow(bool destroyInstance);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    FWCore();
    virtual ~FWCore();

    bool Init(int width, int height);
    int Run(GameCore* pGame);
    void Shutdown();

    void SetWindowSize(int width, int height);

    bool IsKeyDown(int value);
    bool IsMouseButtonDown(int id);
    void GetMouseCoordinates(int* mx, int* my);

    unsigned int GetWindowWidth() { return m_WindowWidth; }
    unsigned int GetWindowHeight() { return m_WindowHeight; }

    void SetEscapeKeyWillQuit(bool value) { m_EscapeKeyWillQuit = value; }

    void SwapBuffers();
};

} // namespace fw

#endif //__FWCore_H__
