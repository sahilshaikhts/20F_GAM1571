#include "Framework.h"
#include "Game.h"
#include "Player.h"

Game::Game(fw::FWCore* pFramework) :fw::GameCore(pFramework)
{
    player = new Player(GameCore);
    
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

    delete player;

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

    player->Update();
    ImGui::ShowDemoWindow();
}

void Game::Draw()
{
    glClearColor(0.6f, 0.96f, 0.26f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    player->Draw();
    uiManager->EndFrame();
}

void Game::SetVec2(float x,float y)
{
    pos.x = x;
    pos.y = y;
}

void Game::Human()
{
    m_pMesh->SetDrawMode(4);

    //Hair
    {
        SetVec2(120, 580);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(160, 570);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(120, 580);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(125, 565);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //Face
    {
        SetVec2(125, 565);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(120, 525);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(170, 525);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(163, 553);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //Torso
    {
        SetVec2(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(170, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(190, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(100, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(190, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //LEGS
    {   SetVec2(100, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    SetVec2(90, 225);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    SetVec2(145, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    SetVec2(190, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    SetVec2(200, 225);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

    SetVec2(145, 385);
    m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //ARM LEFT
    {
        SetVec2(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(80, 490);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(50, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(120, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(120, 460);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(50, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(50, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(100, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(80, 440);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }
    //ARM RIGHT
    {
        SetVec2(170, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(210, 490);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(240, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(170, 522);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(170, 460);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(240, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(240, 400);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(190, 385);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(210, 440);
        m_pMesh->AddVertex(m_pMesh->ConvertScreenToWorldPosition(pos));
    }

    fw::GameObject* h=new fw::GameObject();
    h->SetMesh(m_pMesh);
    h->SetShader(m_pShader);
    objects.push_back(h);
}

void Game::Animal()
{    
    fw::Mesh* lMesh=new fw::Mesh();
    
    lMesh->SetDrawMode(4);
    //HEAD
    {
        SetVec2(560, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(500, 360);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(500, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(500, 360);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(500, 390);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(520, 330);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));
    }

    //BODY
    {
        SetVec2(500, 280);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(400, 290);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(500, 340);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(400, 290);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(400, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(500, 340);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

    }

    //Legs
    {
        SetVec2(400, 320);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(380, 300);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(400, 200);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));


        SetVec2(500, 280);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));
        
        SetVec2(470, 210);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));

        SetVec2(470, 290);
        lMesh->AddVertex(lMesh->ConvertScreenToWorldPosition(pos));


    }

    player->SetMesh(lMesh);
    player->SetShader(m_pShader);
    
   // objects.push_back(h);
}
