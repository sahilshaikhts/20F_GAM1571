#include"Framework.h"
class RemoveFromGameEvent :public fw::Event
{

public:
	
	RemoveFromGameEvent(fw::GameObject* obj) { object = obj;}
	virtual ~RemoveFromGameEvent(){}

	static const char* GetStaticEventType() { return "RemoveFromGameEvent"; }
	virtual const char* GetType() override { return GetStaticEventType(); }
	fw::GameObject* GetObject() { return object; }

private:
	fw::GameObject* object=nullptr;

};

class CollisionEvent :public fw::Event
{
public:
	CollisionEvent(fw::GameObject* ahandler, fw::GameObject* aOther) { handler = ahandler; other = aOther; }
	virtual ~CollisionEvent() {}
	static const char* GetStaticEventType() { return "CollisionEvent"; }
	virtual const char* GetType() override { return GetStaticEventType(); }
	void NotifyHandler() { handler->OnCollision(other); }
private:
	fw::GameObject* handler=nullptr;
	fw::GameObject* other= nullptr;

};