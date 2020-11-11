#include "GamePCH.h"
#include"Player.h"
#include "Objects/PlayerController.h"
Player::Player(fw::GameCore* aCore,PlayerController* controller, std::string aName, vec4 aColor) :fw::GameObject(aCore, aName, aColor)
{
	speed = 5;
	position += vec2(1, 1);
	frameWork = aCore->GetFrameWork();
	m_controller = controller;
	radius = 0.4f;//change this

	collider = new CircleCollider(this,aCore->GetEventManager(),radius,vec2(0,0));
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
	collider->Update(deltaTime);
}

void Player::OnCollision(GameObject* other, CollisionState state)
{
	if (other->GetName() == "Enemy" && state == CollisionState::Entered) {
		inputEnabled = false;
	}
}




