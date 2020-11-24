#pragma once
class PlayerController;
class Player :public fw::GameObject
{
	class SpriteSheet;
private:
	fw::FWCore* frameWork;
	fw::SpriteSheet* m_spriteSheet;
	float speed, invincibilityTimer;
	bool isSafe, flashRed;
	vec4 nColor;
	PlayerController* m_controller;
public:
	int lives;
	float radius;
	bool inputEnabled=true;
	Player(fw::GameCore* aCore, PlayerController* controller, std::string aName,char* spriteFName,vec4 aColor);
	void Update(float deltaTime) override;
	void Player::OnCollision(GameObject* other, fw::CollisionState aState) override;

};

