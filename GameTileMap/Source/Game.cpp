#include "GamePCH.h"
#include "Game.h"

#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Enemy.h"
#include "Objects/Shape.h"

#include "Events/GameEvents.h"
#include<time.h>


//NOTE:Handle game states in winmain?

Game::Game(fw::FWCore* pFramework) :fw::GameCore(pFramework)
{

}


Game::~Game()
{
    for (std::pair<std::string, fw::ShaderProgram*> cShader : m_shaders)
    {
        delete cShader.second;
    }
    if (m_pEventManager != nullptr)
    {
        delete m_pEventManager;
        m_pEventManager = nullptr;
    }
    if (m_controller != nullptr)
        delete m_controller;

    if (uiManager != nullptr)
        delete uiManager;
    
    if (texture_player != nullptr)
        delete texture_player;
    
    if (mesh_player != nullptr)
        delete mesh_player;

    if (player != nullptr)
        delete player;
}

void Game::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    uiManager = new fw::ImGuiManager(m_pFramework);
    uiManager->Init();

    m_pEventManager = new fw::EventManager();
    m_controller = new PlayerController();

    m_shaders["Basic"] = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    mesh_player = new fw::Mesh();

    mesh_player->SetDrawMode(GL_TRIANGLE_FAN);
    for (int i = 0; i < totalVerts_heart; i++) {
        mesh_player->AddVertex(shape_sprite[i]);//meshLives->CreateCircle(6, .15);
    }
    player = new Player(this, m_controller, "Player", "Data/Texture/Zelda.json", vec4(.18f, .15f, .18f, 1));
    texture_player = new fw::Texture("Data/Texture/Zelda.png");
    player->SetMesh(mesh_player);
    player->SetShader(m_shaders["Basic"]);
    player->SetTexture(texture_player);
    objects.push_back(player);


    gameState = fw::GameState::Start;
    GameStart();//Direct function call instead of even to avoid delay in initializing pointers
}


void Game::StartFrame(float deltaTime)
{
    uiManager->StartFrame(deltaTime);

    m_controller->StartFrame();
    m_pEventManager->DispatchAllEvents(this);
}

void Game::Update(float deltaTime)
{
    wglSwapInterval(vSync ? 1 : 0);

    if (gameState == fw::GameState::Playing) {
        for (auto it = objects.begin(); it != objects.end(); it++)
        {
            fw::GameObject* obj = *it;
            obj->Update(deltaTime);
        }
    }
    DebugUI();

    timer += deltaTime;
}

void Game::DebugUI()
{
    ImGui::Text("TIME :%.f", timer);
}
void Game::Draw()
{
    glClearColor(0.7f, 0.75f, 0.8f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameState == fw::GameState::Playing && objects.size() != 0)
    {
        for (auto obj : objects)
        {
            obj->Draw();
        }
    }
    uiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{

    if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
    {
        fw::InputEvent* event = static_cast<fw::InputEvent*>(pEvent);

        if (event->GetKeyCode() == 'R') {

            fw::Event* endEvent = new GameStateChangeEvent(fw::GameState::Restart);
            GetEventManager()->AddEvent(endEvent);
        }
        else
            m_controller->OnEvent(pEvent);

    }
    if (pEvent->GetType() == CollisionEvent::GetStaticEventType())
    {
        CollisionEvent* event = static_cast<CollisionEvent*>(pEvent);
        event->NotifyHandler();
    }

    if (pEvent->GetType() == GameStateChangeEvent::GetStaticEventType())
    {
        GameStateChangeEvent* event = static_cast<GameStateChangeEvent*>(pEvent);
        switch (event->GetNewState())
        {
        case fw::GameState::Start:
            GameStart();
            break;

        case fw::GameState::Playing:
            GamePlaying();
            break;

        case fw::GameState::Paused:
            if (gameState == fw::GameState::Paused)//will stay paused until pause event is created again to resume
                GameResume();
            else
                GamePaused();
            break;

        case fw::GameState::Won:
            GameEnd(fw::GameState::Won);
            break;

        case fw::GameState::Lost:
            GameEnd(fw::GameState::Lost);
            break;

        case fw::GameState::End:
            GameEnd(fw::GameState::End);
            break;

        case fw::GameState::Restart:
            GameRestart();
            break;

        }
    }

    //SHOULD REMAIN THE LAST EVENT TO BE HANDLED
    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* removeEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* target = removeEvent->GetObject();
        auto it = std::find(objects.begin(), objects.end(), target);
        objects.erase(it);

        delete target;
    }
}
void Game::GameStart()
{
    srand(time(0));
    timer = 0;

    gameState = fw::GameState::Playing;
}
void Game::GamePlaying()
{

}
void Game::GamePaused()
{

}
void Game::GameResume()
{

}
void Game::GameRestart()
{
    gameState = fw::GameState::Restart;
    for (fw::GameObject* obj : objects)
    {
        delete obj;
    }
    objects.clear();
    fw::Event* event = new GameStateChangeEvent(fw::GameState::Start);
    GetEventManager()->AddEvent(event);

}
void Game::GameEnd(fw::GameState endState)
{
    if (endState == fw::GameState::Lost)
    {
        fw::Event* endEvent = new GameStateChangeEvent(fw::GameState::Restart);
        GetEventManager()->AddEvent(endEvent);
    }
    else  if (endState == fw::GameState::Won)
    {
    }
    else if (endState == fw::GameState::End)
    {

    }

}
