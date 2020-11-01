#include "GamePCH.h"
#include"Player.h"
#include"Game.h"

Player::Player(fw::GameCore* aCore, std::string aName,vec4 aColor) :fw::GameObject(aName)
{
	if (aCore != nullptr)
		frameWork = aCore->GetFrameWork();
	
	color = aColor;
	speed = 5;
	position +=vec2(1, 1);

}
void Player::Update(float deltaTime)
{
	ImGui::InputFloat("PosX", &position.x, 0.1f, 1.0f, "%.3f");
	ImGui::InputFloat("PosY", &position.y, 0.1f, 1.0f, "%.3f");
	vec2 dir(0, 0);
	if (frameWork->IsKeyDown('d') || frameWork->IsKeyDown('D'))
	{
		dir.x = 1;
	}

	if (frameWork->IsKeyDown('a') || frameWork->IsKeyDown('A'))
	{
		dir.x = -1;
	}

	if (frameWork->IsKeyDown('w') || frameWork->IsKeyDown('W'))
	{
		dir.y = 1;
	}

	if (frameWork->IsKeyDown('s') || frameWork->IsKeyDown('S'))
	{
		dir.y = -1;
	}

	position += dir * speed * deltaTime;

	//static_cast<Game>(frameWork)
}




