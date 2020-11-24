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
	m_UVOffset = vec2(83.0f / 256.0f, 112.0f / 128.0f);
	m_UVScale = vec2(16.0f / 256.0f, 16.0f / 128.0f);
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

	if (invincibilityTimer > 0)
	{
		invincibilityTimer -= deltaTime;
		if (invincibilityTimer <= 0)
			color.a =1;
	}
}

void Player::OnCollision(GameObject* other, fw::CollisionState aState)
{
	if (other->GetName() == "Enemy"|| other->GetName() == "Enemy_2" || other->GetName() == "Spike" && invincibilityTimer<=0) {
		if (aState == fw::CollisionState::Entered)
			if (lives > 1) {
				lives--;
				if(other->GetName() == "Enemy")
				m_Core->GetEventManager()->AddEvent(new RemoveFromGameEvent(other));
				invincibilityTimer = 1.5f;
				color.a = .5f;
			}
			else
			{
				m_Core->GetEventManager()->AddEvent(new GameStateChangeEvent(fw::GameState::Lost));
			}
	}
}




