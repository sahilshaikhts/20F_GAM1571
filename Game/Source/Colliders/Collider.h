#pragma once
class Collider
{
protected:
	std::vector<Collider*> collidingObjects;
	fw::GameObject* parentObject;
	fw::EventManager* eventManager;
	fw::vec2 offset;

public:
	static std::vector<Collider*> allColliders;//remove element when a game objects deletes
	enum class ColliderShape {
		circle,
		rectangle,
	};
	fw::vec2 position;
	
	ColliderShape shape;
	bool isEnabled;

	virtual void Update(float deltaTime) =0;
};

