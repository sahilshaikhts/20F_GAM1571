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

	CollisionEvent(fw::GameObject* ahandler, fw::GameObject* aOther, CollisionState aState) { handler = ahandler; other = aOther; state = aState; }
	virtual ~CollisionEvent() {}
	static const char* GetStaticEventType() { return "CollisionEvent"; }
	virtual const char* GetType() override { return GetStaticEventType(); }
	void NotifyHandler() { handler->OnCollision(other,state); }

private:
	fw::GameObject* handler = nullptr;
	fw::GameObject* other = nullptr;
	CollisionState state;
};
class GameStateChangeEvent :public fw::Event
{
public:

	GameStateChangeEvent(fw::GameState aNewState) { newState = aNewState; }
	virtual ~GameStateChangeEvent() {}
	static const char* GetStaticEventType() { return "GameStateChangeEvent"; }
	virtual const char* GetType() override { return GetStaticEventType(); }
	fw::GameState GetNewState() { return newState; }

private:
	fw::GameState newState;

};

