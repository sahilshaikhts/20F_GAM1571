#include"Framework.h"
class RemoveFromGameEvent :public fw::Event
{

public:
	
	RemoveFromGameEvent(fw::GameObject* obj) { object = obj; eventType="RemoveFromGameEvent"; }
	virtual ~RemoveFromGameEvent(){}

	static const char* GetStaticEventType() { return "RemoveFromGameEvent"; }
	virtual const char* GetType() override { return GetStaticEventType(); }

	fw::GameObject* GetObject() { return object; }

private:
	fw::GameObject* object=nullptr;

};