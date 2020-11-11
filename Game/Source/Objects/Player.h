#pragma once
class PlayerController;
class CircleCollider;
class Player :public fw::GameObject
{
	fw::FWCore* frameWork;
	float speed;
	PlayerController* m_controller;
	CircleCollider* collider;
public:
	vec2 boundsCenter;
	float boundsRadius, radius;
	bool inputEnabled=true;
	Player(fw::GameCore* aCore, PlayerController* controller, std::string aName,vec4 aColor);
	void Update(float deltaTime) override;
	void OnCollision(GameObject* other, CollisionState state) override;
	int col = 0;
};

