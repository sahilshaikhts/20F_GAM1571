#pragma once
class PlayerController;
class Player :public fw::GameObject
{
	fw::FWCore* frameWork;
	float speed;
	PlayerController* m_controller;
public:
	vec2 boundsCenter;
	float boundsRadius, radius;
	bool inputEnabled=true;
	Player(fw::GameCore* aCore, PlayerController* controller, std::string aName,vec4 aColor);
	void Update(float deltaTime) override;
	void Player::OnCollision(GameObject* other) override;

};

