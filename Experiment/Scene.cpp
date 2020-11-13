#include "GamePCH.h"
#include "Scene.h"

#include "Objects/Player.h"
#include "Objects/PlayerController.h"
#include "Objects/Enemy.h"
#include "Objects/Shape.h"

#include "Events/GameEvents.h"
#include<time.h>


//NOTE:Handle Scene states in winmain?

Scene::Scene(fw::FWCore* pFramework) :fw::GameCore(pFramework)
{
}


Scene::~Scene()
{
    delete uiManager;


    for (fw::GameObject* obj : objects)
    {
        delete obj;
    } 
}

void Scene::Init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    srand(time(0));
  
    uiManager = new fw::ImGuiManager(m_pFramework);
    uiManager->Init();
    m_pEventManager = new fw::EventManager();

   }


void Scene::StartFrame(float deltaTime) 
{
}
void Scene::Update(float deltaTime)
{
    m_pEventManager->DispatchAllEvents(this);
    uiManager->StartFrame(deltaTime);
    wglSwapInterval(vSync ? 1 : 0);

}


void Scene::Draw()
{
    glClearColor(0.6f, 0.96f, 0.26f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto obj : objects)
    {
        obj->Draw();
    }

    uiManager->EndFrame();
}

void Scene::OnEvent(fw::Event* pEvent)
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

