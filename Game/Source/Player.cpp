#include"Player.h"

	void Player::Update()
	{
		if (frameWork->IsKeyDown(0))
		{
			position.x = .05f;
		}
	}

	Player::Player(fw::GameCore* fw)
	{
		frameWork = fw;
	}

	void Player::Draw()
	{
		GameObject::Draw();
	}
