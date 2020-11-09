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

class Collision :public fw::Event 
{
public:
	Collision(fw::GameObject* ahandler, fw::GameObject* aOther) { handler = ahandler; other = aOther; }
	static const char* GetStaticEventType() { return "Collision"; }
	virtual const char* GetType() override { return GetStaticEventType(); }

private:
	fw::GameObject* handler;
	fw::GameObject* other;

};