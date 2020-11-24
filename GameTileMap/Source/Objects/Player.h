#pragma once
class PlayerController;
class Player :public fw::GameObject
{

	enum AnimState
	{
		stop=-1,
		right=0,
		left=2,
		up=4,
		down=6
	};
	class SpriteSheet;
private:
	fw::FWCore* frameWork;
	float speed, invincibilityTimer;
	float animTimer;
	bool isSafe, flashRed;
	vec4 nColor;
	AnimState m_animState;
	PlayerController* m_controller;
public:
	int lives;
	float radius;
	bool inputEnabled=true;
	fw::SpriteSheet* m_spriteSheet;
	Player(fw::GameCore* aCore, PlayerController* controller, std::string aName,char* spriteFName,vec4 aColor);

	~Player();
	void Update(float deltaTime) override;
	void Player::OnCollision(GameObject* other, fw::CollisionState aState) override;

};

