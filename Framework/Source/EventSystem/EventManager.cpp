#include "FrameworkPCH.h"
#include"Event.h"

#include "EventManager.h"
#include"Core/GameCore.h"

namespace fw{
	EventManager::EventManager()
	{

	}
	EventManager::~EventManager()
	{

	}
	void EventManager::AddEvent(Event* pEvent)
	{
		m_EventQueue.push(pEvent);
	}
	void EventManager::DispatchAllEvents(GameCore* pGameCore)
	{
		while (m_EventQueue.empty() == false)
		{
			Event* event=m_EventQueue.front();
			m_EventQueue.pop();
			pGameCore->OnEvent(event);
			delete event;
		}
	}
}
