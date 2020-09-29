#include"Player.h"
#include "Utility/Helpers.h"
#include "Utility/ShaderProgram.h"
	void Player::Update()
	{
		position.y = sin(fw::GetSystemTimeSinceGameStart()*2) * 0.25f;  //this line is to demonstrate that everthing else is working apart from the input.

		if (frameWork->IsKeyDown(64))
		{
			position.x = .05f;
		}
	}

	Player::Player(fw::FWCore* aCore)
	{
		frameWork = aCore;
		previousTime = fw::GetSystemTimeSinceGameStart();

	}

	
