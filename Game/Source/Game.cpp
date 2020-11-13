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
    if (m_pShader != nullptr) {
        delete m_pShader;
        m_pShader = nullptr;
    }
    if (m_pMesh != nullptr) {
        delete m_pMesh;
        m_pMesh = nullptr;
    }

    if (mesh_spike != nullptr)
    {
        delete mesh_spike;
        mesh_spike = nullptr;
    }

    delete uiManager;


    for (fw::GameObject* obj : objects)
    {
        delete obj;
    }
}

void Game::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    srand(time(0));
    gameState = fw::GameState::Start;
    spawnInterval = 2;
    lastSpawnTime = 0;
    timer = 0;
    countdown = 10;
    arenaCenter = vec2(5, 5);
    arenaRadius = 4;
    uiManager = new fw::ImGuiManager(m_pFramework);
    uiManager->Init();
    m_pEventManager = new fw::EventManager();

    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");

    GetEventManager()->AddEvent(new GameStateChangeEvent(fw::GameState::Start));
}


void Game::StartFrame(float deltaTime)
{
}

void Game::Update(float deltaTime)
{
    m_pEventManager->DispatchAllEvents(this);
    uiManager->StartFrame(deltaTime);
    wglSwapInterval(vSync ? 1 : 0);


    if (gameState == fw::GameState::Playing) {
        for (auto it = objects.begin(); it != objects.end(); it++)
        {
            fw::GameObject* obj = *it;
            obj->Update(deltaTime);
        }
        if (timer > lastSpawnTime + spawnInterval) {
                int type = rand() % 10;
                if (type < 5 && currentWave >= 3)
                    SpawnBouncingEnemy();
                else
                    SpawnEnemy();

            lastSpawnTime = timer;
        }
        DebugUI();

        if (lives != player->lives && lives > 0)
        {
            ui_lives[lives - 1]->isVisible = false;
            lives = player->lives;
        }
    if (countdown <= 0)
    {
        //call wave up event
        gameState = fw::GameState::Won;
        GetEventManager()->AddEvent(new GameStateChangeEvent(fw::GameState::Won));
    }
    }
    countdown -= deltaTime;
    timer += deltaTime;
}

void Game::DebugUI() {
    //Object's list

    ImGui::Text("WAVE %d", currentWave);
    if (gameState == fw::GameState::Playing) {
        ImGui::SameLine();
        ImGui::Text("| TIME LEFT %.f", countdown);
    }
    if (gameState == fw::GameState::Won)
        ImGui::Text("WAVE COMPLETE!!");

}
void Game::Draw()
{
    glClearColor(0.7f, 0.85f, 0.87f, 1);
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
    lives = 3;
    currentWave = 1;
    enemyMaxSpeed = 6;
    m_pMesh = new fw::Mesh();
    fw::Mesh* m = new fw::Mesh();
    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");
    m->SetDrawMode(GL_TRIANGLE_FAN);
    m->CreateCircle(40, arenaRadius);

    //Spike mesh
    mesh_spike = new fw::Mesh();
    mesh_spike->SetDrawMode(GL_TRIANGLE_FAN);
    mesh_spike->CreateCircle(3, .3f);

    //Enemy's mesh
    mesh_enemy = new fw::Mesh();
    mesh_enemy->SetDrawMode(GL_TRIANGLE_FAN);
    mesh_enemy->CreateCircle(40, .2f);

    m_controller = new PlayerController();

    fw::GameObject* obj = new fw::GameObject(this, "platform", vec4(1, .92f, 0.9f, 1));//vec4(0.5f, .1f, 0.2f, 1)->for 2nd type of enemy
    obj->SetMesh(m);
    obj->SetShader(m_pShader);
    obj->position = arenaCenter;
    objects.push_back(obj);
    GeneratePlayer();

    //UI
    fw::Mesh* meshLives = new fw::Mesh();
    meshLives->SetDrawMode(GL_TRIANGLE_FAN);
    for (int i = 0; i < totalVerts_heart; i++) {
        meshLives->AddVertex(shape_heart[i]);//meshLives->CreateCircle(6, .15);
    }
    for (int i = 0; i < 3; i++)
    {


        ui_lives[i] = new fw::GameObject(this, "UI_lives", vec4(.9f, .1f, .1f, 1));
        ui_lives[i]->SetMesh(meshLives);
        ui_lives[i]->SetShader(m_pShader);

        ui_lives[i]->position = vec2(.5f + (i * .6f), 9.5f);

        objects.push_back(ui_lives[i]);
    }
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
    if (m_pShader != nullptr) {

        delete m_pShader;

        m_pShader = nullptr;
    }
    if (m_pMesh != nullptr) {
        delete m_pMesh;
        m_pMesh = nullptr;
    }
    if (mesh_spike != nullptr)
    {
        delete mesh_spike;
        mesh_spike = nullptr;
    }

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
        if (currentWave == 1)
        {
            enemyMaxSpeed +=1 ;
            countdown = 5;
        }
        else if (currentWave == 2)
        {
            countdown = 20;
        }else if (currentWave == 3)
        {
            countdown = 30;
        }else if (currentWave == 4)//last
        {
            enemyMaxSpeed +=1 ;
            countdown = 40;
        }
        if (player->lives < 3) {
            player->lives++;
            ui_lives[lives]->isVisible = true;
            lives = player->lives;
        }
        currentWave++;
        

        if (currentWave >= 4) {
            for (int i = rand() % 4 + 2; i > 0; i--)
            {
                SpawnSpikes();
            }
        }
        
        gameState = fw::GameState::Playing;
    }
    else if (endState == fw::GameState::End)
    {

    }

}


void Game::GeneratePlayer()
{
    fw::Mesh* lMesh = new fw::Mesh();

    lMesh->SetDrawMode(GL_TRIANGLE_FAN);
    lMesh->CreateCircle(180, .4f);

    Player* pl = new Player(this, m_controller, "Player", vec4(.18f, .15f, .18f, 1));
    player = pl;
    pl->SetMesh(lMesh);
    pl->SetShader(m_pShader);
    pl->boundsCenter = arenaCenter;
    pl->boundsRadius = arenaRadius;
    pl->radius = .4f;

    objects.push_back(pl);

}

void Game::SpawnEnemy()
{

    float rad = rand() % 360;
    vec2 randomDir(cos(rad), sin(rad));
    vec2 pos = arenaCenter + (randomDir * arenaRadius);
    rad = rand() % 45;
    vec2 randOffset(cos(rad), sin(rad));

    vec2 velocity = (pos - (arenaCenter - randOffset)).GetNormalized();

    Enemy* newEn = new Enemy(this, player, pos, velocity, vec4(.9f, .2f, .3f, 1)/*vec4(.9f,.2f,.3f,1)*/, mesh_enemy, arenaCenter, arenaRadius, .2f);
    newEn-> speed = rand() % enemyMaxSpeed + 4;

    newEn->SetShader(m_pShader);
    newEn->physicalCollider = false;
    newEn->m_name = "Enemy";

    objects.push_back(newEn);

}

void Game::SpawnBouncingEnemy()
{

    float rad = rand() % 360;
    vec2 randomDir(cos(rad), sin(rad));
    vec2 pos = arenaCenter + (randomDir * arenaRadius);
    rad = rand() % 45;
    vec2 randOffset(cos(rad), sin(rad));

    vec2 velocity = (pos - (arenaCenter - randOffset)).GetNormalized();

    Enemy* newEn = new Enemy(this, player, pos, velocity, vec4(.87f, .43f, .32F, 1)/*vec4(.9f,.2f,.3f,1)*/, mesh_enemy, arenaCenter, arenaRadius, .2f);
    newEn->SetShader(m_pShader);
    newEn->speed = rand() % 6 +2;
    newEn->physicalCollider = true;
    newEn->m_name = "Enemy_2";
    objects.push_back(newEn);

}

void Game::SpawnSpikes()
{
    float rad = rand() % 360;
    
    vec2 pos = vec2(cos(rad),sin(rad));
    pos.Normalize();
    vec2 randOffset=vec2(rand()%4+2, rand() % 4+2);
    
    Enemy* newEn = new Enemy(this, player, pos+(arenaCenter+randOffset), vec2(0,0), vec4(.87f, .43f, .32F, 1)/*vec4(.9f,.2f,.3f,1)*/, mesh_enemy, arenaCenter, arenaRadius, .2f);
    
    newEn->SetMesh(mesh_spike);
    newEn->SetShader(m_pShader);
    
    newEn->m_name = "Spike";
    objects.push_back(newEn);

}
