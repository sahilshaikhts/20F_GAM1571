#pragma once

namespace fw {

class Event;
class GameCore;

class EventManager
{
public:
    EventManager();
    ~EventManager();

    void AddEvent(Event* pEvent);
    void DispatchAllEvents(GameCore* pGameCore);

protected:
    std::queue<Event*> m_EventQueue;
};

} // namespace fw
