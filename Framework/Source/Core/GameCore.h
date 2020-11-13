#pragma once

namespace fw {
    class Event;
    class EventManager;
    class GameObject;
    class FWCore;

    enum class GameState {
    Off,
    Start,
    Playing,
    Paused,
    Won,
    Lost,
    Restart,
    End,
};
    enum class CollisionState
    {
        Idle,
        Entered,
        Colliding,
        Exited
    };
class GameCore
{
public:
    GameCore(FWCore* pFramework);
    virtual ~GameCore();

    virtual void StartFrame(float deltaTime) =0;
    virtual void OnEvent(Event* pEvent) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;
    FWCore* GetFrameWork()
    {
        return m_pFramework;
    }
    fw::EventManager* GetEventManager()
    {
        return m_pEventManager;
    }
protected:
    FWCore* m_pFramework;
    fw::EventManager* m_pEventManager = nullptr;

};

} // namespace fw
