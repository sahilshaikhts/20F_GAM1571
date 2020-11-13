	#include "GamePCH.h"
#include"Player.h"
#include "Objects/PlayerController.h"
#include"Events/GameEvents.h"
Player::Player(fw::GameCore* aCore,PlayerController* controller, std::string aName, vec4 aColor) :fw::GameObject(aCore, aName, aColor)
{
	speed = 5;
	position += vec2(1, 1);
	frameWork = aCore->GetFrameWork();
	m_controller = controller;
	nColor = color;
	isSafe = false;
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

	//if (invincibilityTimer > 0)
	//{
	//	invincibilityTimer -= deltaTime;
	//	if(color.r < 0.5f)
	//	color.r -= deltaTime;
	//	color.g
	//	else
	//	color.r += deltaTime;

	//	if (invincibilityTimer <= 0)
	//		color = nColor;
	//}
}

void Player::OnCollision(GameObject* other, fw::CollisionState aState)
{
	if (other->GetName() == "Enemy"|| other->GetName() == "Enemy_2") {
		if (aState == fw::CollisionState::Entered)
			if (lives > 1) {
				lives--;
				if(other->GetName() == "Enemy")
				m_Core->GetEventManager()->AddEvent(new RemoveFromGameEvent(other));
				//invincibilityTimer = 3;
			}
			else
			{
				m_Core->GetEventManager()->AddEvent(new GameStateChangeEvent(fw::GameState::Lost));
			}
	}
}




