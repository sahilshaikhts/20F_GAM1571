#pragma once
class PlayerController;
class Player :public fw::GameObject
{
	class SpriteSheet;
private:
	fw::FWCore* frameWork;
	float speed, invincibilityTimer;
	bool isSafe, flashRed;
	vec4 nColor;
	PlayerController* m_controller;
public:
	int lives;
	float radius;
	bool inputEnabled=true;
	fw::SpriteSheet* m_spriteSheet;
	Player(fw::GameCore* aCore, PlayerController* controller, std::string aName,char* spriteFName,vec4 aColor);
	void Update(float deltaTime) override;
	void Player::OnCollision(GameObject* other, fw::CollisionState aState) override;

};

