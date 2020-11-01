#include "GamePCH.h"
#include "Game.h"
#include "Objects/Player.h"
#include "Objects/Shape.h"
#include "Events/GameEvents.h"
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
    uiManager = new fw::ImGuiManager(m_pFramework);
    uiManager->Init();
    m_pEventManager = new fw::EventManager();

    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");
    m_pMesh = new fw::Mesh();
    fw::Mesh* m = new fw::Mesh();
    
    m->CreateCircle(20, 8);
    fw::GameObject* obj = new fw::GameObject(*this);
    obj->SetMesh(m);
    obj->SetShader(m_pShader);
    obj->position = vec2(5, 5);
    obj->color = vec4(1, 0, 0, 1);
    objects.push_back(obj);
    
   }

void Game::Update(float deltaTime)
{
    m_pEventManager->DispatchAllEvents(this);
    uiManager->StartFrame(deltaTime);
    ImGui::ShowDemoWindow();
    
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        fw::GameObject* obj = *it;

        obj->Update(deltaTime);

        ImGui::PushID(obj);
        ImGui::Text("Name: %s", obj->GetName().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete"))
        {
            m_pEventManager->AddEvent(new RemoveFromGameEvent(obj));
        }
        ImGui::PopID();
    }

    ImGui::Checkbox("V-Sync", &v);
    wglSwapInterval(v? 1 : 0);

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
    if (pEvent->GetType() == RemoveFromGameEvent::GetStaticEventType())
    {
        RemoveFromGameEvent* removeEvent = static_cast<RemoveFromGameEvent*>(pEvent);
        fw::GameObject* target = removeEvent->GetObject();
        auto it = std::find(objects.begin(), objects.end(), target);
        objects.erase(it);

        delete target;
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

void Game::Animal()
{    
    fw::Mesh* lMesh=new fw::Mesh();
    
    lMesh->SetDrawMode(GL_TRIANGLE_FAN);
    vec4 g;
    Player* pl = new Player(this, "Triangle",g.DarkGreen());
    lMesh->CreateCircle(360, 2);

    pl->SetMesh(lMesh);
    pl->SetShader(m_pShader);
    objects.push_back(pl);
}
