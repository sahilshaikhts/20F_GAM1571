	#include "GamePCH.h"
#include"Player.h"
#include "Objects/PlayerController.h"
Player::Player(fw::GameCore* aCore,PlayerController* controller, std::string aName, vec4 aColor) :fw::GameObject(aCore, aName, aColor)
{
	speed = 5;
	position += vec2(1, 1);
	frameWork = aCore->GetFrameWork();
	m_controller = controller;
}

void Player::Update(float deltaTime)
{
	if (inputEnabled)
	{
		vec2 dir(0, 0);

		if (m_controller->IsHeld(PlayerController::Mask::Right))
		{
			dir.x = 1;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Left))
		{
			dir.x = -1;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Up))
		{
			dir.y = 1;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Down))
		{
			dir.y = -1;
		}

		position += dir * speed * deltaTime;
	}

	if (position.GetDistance(boundsCenter) > boundsRadius - radius)
	{
		position = boundsCenter + ((position - boundsCenter).GetNormalized() * (boundsRadius - radius));
	}

}

void Player::OnCollision(GameObject* other)
{
	if (other->GetName()=="Enemy") {
		inputEnabled = false;
	}
}




