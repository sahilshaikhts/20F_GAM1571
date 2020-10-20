#include "GamePCH.h"

#include "Game.h"
#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Shapes.h"
#include "Events/GameEvents.h"

Game::Game(fw::FWCore* pFramework) : fw::GameCore( pFramework )
{
    wglSwapInterval( m_VSyncEnabled ? 1 : 0 );
}

Game::~Game()
{
    delete m_pShader;
    delete m_pMeshHuman;
    delete m_pMeshEnemy;
    delete m_pMeshTest;

    for( fw::GameObject* pObject : m_Objects )
    {
        delete pObject;
    }

    delete m_pPlayerController;

    delete m_pEventManager;
    delete m_pImGuiManager;
}

void Game::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( m_pFramework );
    m_pImGuiManager->Init();

    m_pEventManager = new fw::EventManager();

    // Load some shaders.
    m_pShader = new fw::ShaderProgram( "Data/Basic.vert", "Data/Basic.frag" );

    // Create some meshes.
    m_pMeshHuman = new fw::Mesh( meshPrimType_Human, meshNumVerts_Human, meshAttribs_Human );
    m_pMeshEnemy = new fw::Mesh( meshPrimType_Enemy, meshNumVerts_Enemy, meshAttribs_Enemy );

    m_pMeshTest = new fw::Mesh();

    int numPoints = 3;
    {
        //float arr[numPoints*2] = { 0 }; //{ 0,0,   1,0,   2,0 };
        //float* arr = new float[numPoints*2];
        std::vector<float> arr;

        for( int i=0; i<numPoints*2; i++ )
            arr.push_back( 0 );

        for( int i=0; i<numPoints; i++ )
        {
            arr[i*2] = (float)i;
        }
        
        m_pMeshTest->CreateShape( GL_POINTS, numPoints, &arr[0] );
    }

    m_pPlayerController = new PlayerController();
    
    m_Arena = new fw::Mesh();
    m_Arena->CreateCircle(5, vertices, true);

    fw::Mesh* meshPlayer=new fw::Mesh();
    meshPlayer->CreateCircle(.5f, vertices, true);

    // Create some GameObjects.
    m_Objects.push_back( new Player( this, m_pPlayerController, "Player", vec2( 6, 5 ), meshPlayer, m_pShader, vec4::Blue() ) );
    m_Objects.push_back(new fw::GameObject(this, "GO", vec2(5, 5), m_Arena, m_pShader, vec4::Green()));


    }

void Game::OnEvent(fw::Event* pEvent)
{
    m_pPlayerController->OnEvent( pEvent );

    if( pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType() )
    {
        RemoveFromGameEvent* pRemoveFromGameEvent = static_cast<RemoveFromGameEvent*>( pEvent );
        fw::GameObject* pObject = pRemoveFromGameEvent->GetGameObject();

        auto it = std::find( m_Objects.begin(), m_Objects.end(), pObject );
        m_Objects.erase( it );

        delete pObject;
    }
}

void Game::Update(float deltaTime)
{
    // Process our events.
    m_pEventManager->DispatchAllEvents( this );

    m_pImGuiManager->StartFrame( deltaTime );
    ImGui::ShowDemoWindow();

    m_Arena->CreateCircle(5, vertices, false);

    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;

        pObject->Update( deltaTime );
    }

    // Debug imgui stuff.
    {
        if( ImGui::Checkbox( "VSync", &m_VSyncEnabled ) )
        {
            wglSwapInterval( m_VSyncEnabled ? 1 : 0 );
        }
        ImGui::DragInt("Vertices", &vertices, 1, 3, 100);
    }
}

void Game::Draw()
{
    glClearColor( 0, 0, 0.2f, 0 );
    glClear( GL_COLOR_BUFFER_BIT );

    glPointSize( 10 );
    
    for( auto it = m_Objects.begin(); it != m_Objects.end(); it++ )
    {
        fw::GameObject* pObject = *it;

        pObject->Draw();
    }

    m_pImGuiManager->EndFrame();
}
