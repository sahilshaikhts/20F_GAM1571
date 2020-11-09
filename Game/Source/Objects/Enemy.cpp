#include "GamePCH.h"
#include"Enemy.h"
#include "Events/GameEvents.h"
#include"Objects/Player.h"
Enemy::Enemy(fw::GameCore* core, Player* aPlayer, vec2 startPosition, vec2 aDir, vec4 aColor,fw::Mesh* aMesh, vec2 aBoundsCenter, float aBoundsRadius, float aRadius)
{
	m_Core = core;
	player = aPlayer;

	direction = aDir;
	speed = rand()%8+4;

	position = startPosition;
	
	color = aColor;
	mesh = aMesh;
	m_name = "Enemy";

	boundsCenter = aBoundsCenter;
	boundsRadius = aBoundsRadius;
	radius = aRadius;
}

void Enemy::Update(float deltaTime)
{
	position -= direction * speed*deltaTime;
	if (position.GetDistance(boundsCenter) > boundsRadius)
	{
		m_Core->GetEventManager()->AddEvent(new RemoveFromGameEvent(this));
	}
	if (position.GetDistance(player->position) <radius+player->radius)
	{
		CollisionEvent* obj = new CollisionEvent(player, this);
 		m_Core->GetEventManager()->AddEvent(obj);
	}
}