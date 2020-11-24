#include "GamePCH.h"
#include"Enemy.h"
#include "Events/GameEvents.h"
#include"Objects/Player.h"
Enemy::Enemy(fw::GameCore* core, Player* aPlayer, vec2 startPosition, vec2 aDir, vec4 aColor, fw::Mesh* aMesh, vec2 aBoundsCenter, float aBoundsRadius, float aRadius)
{
	speed = 0;
	m_Core = core;
	player = aPlayer;

	direction = aDir;
	position = startPosition;

	color = aColor;
	mesh = aMesh;
	hp = 100;
	boundsCenter = aBoundsCenter;
	boundsRadius = aBoundsRadius;
	radius = aRadius;
	collisionState = fw::CollisionState::Idle;

}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	position -= direction * speed * deltaTime;

	if (position.GetDistance(player->position) < radius + player->radius)
	{
		CollisionEvent* event;
		if (collisionState == fw::CollisionState::Idle) {
			collisionState = fw::CollisionState::Colliding;

			if (physicalCollider && hp > 0)
			{
				direction.x *= -1;
				direction.y *= -1;
				hp -= 20;
				speed -= .5f;
				color.a -= .1f;
			}

			event = new CollisionEvent(player, this, fw::CollisionState::Entered);
			m_Core->GetEventManager()->AddEvent(event);
		}
		else {
			event = new CollisionEvent(player, this, fw::CollisionState::Colliding);
			m_Core->GetEventManager()->AddEvent(event);
		}

	}
	else
	{
		if (collisionState == fw::CollisionState::Colliding) {
			collisionState = fw::CollisionState::Idle;
			CollisionEvent* event = new CollisionEvent(player, this, fw::CollisionState::Exited);
			m_Core->GetEventManager()->AddEvent(event);
		}
	}
	if (position.GetDistance(boundsCenter) > boundsRadius)
	{
		if (physicalCollider && hp > 0)
		{
			direction.x *= -1;
			direction.y *= -1;
			hp -= 20;
			speed -= .5f;
			color.a -= .1f;
		}
		else
			m_Core->GetEventManager()->AddEvent(new RemoveFromGameEvent(this));
	}
}
