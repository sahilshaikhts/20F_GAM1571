#include "GamePCH.h"
#include "Game.h"
#include<time.h>
#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Enemy.h"

#include "Objects/Shape.h"
#include "Events/GameEvents.h"
//Handle game states in winmain
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
    spawnInterval = 2;
    lastSpawnTime = 0;
    timer = 0;
    
    arenaCenter = vec2(5, 5);
    arenaRadius = 4;
    uiManager = new fw::ImGuiManager(m_pFramework);
    uiManager->Init();
    m_pEventManager = new fw::EventManager();

    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");
    
    //ARENA
    m_pMesh = new fw::Mesh();
    fw::Mesh* m = new fw::Mesh();
    m->SetDrawMode(GL_TRIANGLE_FAN);
    m->CreateCircle(40, arenaRadius);

    //Enemy's mesh
    mesh_enemy = new fw::Mesh();
    mesh_enemy->SetDrawMode(GL_TRIANGLE_FAN);
    mesh_enemy->CreateCircle(40, .2f);
    
    m_controller = new PlayerController();
    {
        fw::GameObject* obj = new fw::GameObject(this, "platform", vec4(0.4f, .5f, 0.5f, 1));
        obj->SetMesh(m);
        obj->SetShader(m_pShader);
        obj->position = arenaCenter;
        objects.push_back(obj); 
    }//ARENA
    GeneratePlayer();
   }


void Game::StartFrame(float deltaTime) 
{
}
void Game::Update(float deltaTime)
{
    m_pEventManager->DispatchAllEvents(this);
    uiManager->StartFrame(deltaTime);
    DebugUI();
    wglSwapInterval(vSync ? 1 : 0);

    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        fw::GameObject* obj = *it;
        obj->Update(deltaTime);
    }
    if (timer > lastSpawnTime + spawnInterval) {
     SpawnEnemy();
     lastSpawnTime = timer;
    }

    timer += deltaTime;
}
void Game::DebugUI() {
    //Object's list
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        fw::GameObject* obj = *it;
        ImGui::PushID(obj);
        ImGui::Text("Name: %s", obj->GetName().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            m_pEventManager->AddEvent(new RemoveFromGameEvent(obj));
        }
        ImGui::PopID();
    }

    ImGui::Checkbox("V-Sync", &vSync);
 
}
void Game::Draw()
{
    glClearColor(0.6f, 0.96f, 0.26f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto obj : objects)
    {
        obj->Draw();
    }

    uiManager->EndFrame();
}

void Game::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == fw::InputEvent::GetStaticEventType())
        m_controller->OnEvent(pEvent);

    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* removeEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* target = removeEvent->GetObject();
        auto it = std::find(objects.begin(), objects.end(), target);
        objects.erase(it);

        delete target;
    }
    if (pEvent->GetType() == CollisionEvent::GetStaticEventType())
    {
        CollisionEvent* event = static_cast<CollisionEvent*>(pEvent);
        event->NotifyHandler();
    }
}





void Game::Human()
{
    m_pMesh->SetDrawMode(4);

   /* //Hair
    {
        pos.Set(120, 580);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(160, 570);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(120, 580);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(125, 565);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //Face
    {
        pos.Set(125, 565);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(120, 525);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(170, 525);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //Torso
    {
        pos.Set(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(170, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(190, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(100, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(190, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //LEGS
    {   pos.Set(100, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    pos.Set(90, 225);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    pos.Set(145, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    pos.Set(190, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    pos.Set(200, 225);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    pos.Set(145, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //ARM LEFT
    {
        pos.Set(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(80, 490);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(50, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(120, 460);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(50, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(50, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(100, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(80, 440);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //ARM RIGHT
    {
        pos.Set(170, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(210, 490);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(240, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(170, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(170, 460);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(240, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(240, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(190, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(210, 440);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }

    fw::GameObject* h=new fw::GameObject();
    h->SetMesh(m_pMesh);
    h->SetShader(m_pShader);
    objects.push_back(h);*/
}

void Game::GeneratePlayer()
{    
    fw::Mesh* lMesh=new fw::Mesh();
    
    lMesh->SetDrawMode(GL_TRIANGLE_FAN);
    lMesh->CreateCircle(180, .4f);

    Player* pl = new Player(this, m_controller,"Player", vec4::White());
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
    vec2 randomDir(cos(rad),sin(rad));
    vec2 pos = arenaCenter+(randomDir * arenaRadius);

    rad = rand() % 45;
    vec2 randOffset(cos(rad), sin(rad));

     vec2 velocity=(pos-(arenaCenter-randOffset)).GetNormalized();

    Enemy* newEn = new Enemy(this,player,pos,velocity, vec4(.12f,.076f,.086f,1)/*vec4(.9f,.2f,.3f,1)*/, mesh_enemy,arenaCenter,arenaRadius,.2f);
    newEn->SetShader(m_pShader);
    objects.push_back(newEn);

}
