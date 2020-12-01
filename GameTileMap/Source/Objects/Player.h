#pragma once
class PlayerController;
class Animation_Player;
class SpriteSheet;

class Player :public fw::GameObject
{

private:
	enum AnimState
	{
		stop = -1,
		left,
		right,
		up,
		down,
	};

	fw::FWCore* frameWork;
	float speed, invincibilityTimer;
	float animTimer;
	bool isSafe, flashRed;
	vec4 nColor;
	PlayerController* m_controller;

	fw::Sprite* currentSprite;
	Animation_Player* m_animation;
	AnimState m_animState;
	
public:
	int lives;
	float radius;
	bool inputEnabled = true;

	Player(fw::GameCore* aCore, PlayerController* controller, std::string aName, vec4 aColor);

	~Player();
	void Update(float deltaTime) override;
	void Player::OnCollision(GameObject* other, fw::CollisionState aState) override;

};

