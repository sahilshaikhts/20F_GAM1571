#include"Player.h"
#include "Utility/Helpers.h"
#include "Utility/ShaderProgram.h"
	void Player::Update(float deltaTime)
	{
		if (frameWork->IsKeyDown('d')|| frameWork->IsKeyDown('D'))
		{
			position.x += 1*deltaTime;
		}

		if (frameWork->IsKeyDown('a') || frameWork->IsKeyDown('A'))
		{
			position.x -= 1 * deltaTime;
		}

		if (frameWork->IsKeyDown('w') || frameWork->IsKeyDown('W'))
		{
			position.y += 1 * deltaTime;
		}

		if (frameWork->IsKeyDown('s') || frameWork->IsKeyDown('S'))
		{
			position.y -= 1 * deltaTime;
		}


	}

	Player::Player(fw::GameCore* aCore)
	{
		if(aCore!=nullptr)
		frameWork = aCore->GetFrameWork();
	}

	
