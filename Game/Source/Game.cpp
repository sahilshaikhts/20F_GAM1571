#include "Framework.h"

#include "Game.h"


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

    m_pShader = new fw::ShaderProgram("Data/Basic.vert", "Data/Basic.frag");
    m_pMesh = new fw::Mesh();
    Human();
    Animal();
}

void Game::Update(float deltaTime)
{
    uiManager->StartFrame(deltaTime);
    ImGui::ShowDemoWindow();
}

void Game::Draw()
{
    glClearColor(0.6f, 0.96f, 0.26f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto obj : objects)
    {
        obj->Draw();
    }

    uiManager->EndFrame();
}

void Game::Human()
{
    Vector2 pos;
    m_pMesh->SetDrawMode(4);

    //Hair
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
    objects.push_back(h);
}

void Game::Animal()
{
    Vector2 pos;
    
    fw::Mesh* lMesh=new fw::Mesh();
    
    lMesh->SetDrawMode(4);
    //HEAD
    {
        pos.Set(560, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(500, 360);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(500, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(500, 360);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(500, 390);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(520, 330);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));
    }

    //BODY
    {
        pos.Set(500, 280);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(400, 290);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(500, 340);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(400, 290);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(400, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(500, 340);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

    }

    //Legs
    {
        pos.Set(400, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(380, 300);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(400, 200);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));


        pos.Set(500, 280);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));
        
        pos.Set(470, 210);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        pos.Set(470, 290);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));


    }
    fw::GameObject* h = new fw::GameObject();

    h->SetMesh(lMesh);
    h->SetShader(m_pShader);
    
    objects.push_back(h);
}
