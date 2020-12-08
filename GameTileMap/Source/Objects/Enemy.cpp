#include "GamePCH.h"
#include"Enemy.h"
#include "Events/GameEvents.h"
#include"Objects/Player.h"
#include"TileMap/Pathfinder.h"
#include"TileMap/TileMap.h"
#include<time.h>

Enemy::Enemy(fw::GameCore* core, TileMap* aTileMap, Player* aPlayer, fw::SpriteSheet* aSpriteSheet, vec2 startPosition,
	vec4 aColor, fw::Mesh* aMesh) :GameObject(core, "Enemy", aColor)
{
	speed = 0;
	m_Core = core;
	player = aPlayer;
	m_spriteSheet = aSpriteSheet;
	sprite_scale = vec2(1, 1);
	// !!!! TEMP(until anim implemented) !!!!
	m_UVScale = m_spriteSheet->GetSpriteInfo("OctorocDown1")->m_UVScale;
	m_UVOffset = m_spriteSheet->GetSpriteInfo("OctorocDown1")->m_UVOffset;

	direction = vec2(0, 0);
	position = startPosition;

	color = aColor;
	mesh = aMesh;
	hp = 100;
	collisionState = fw::CollisionState::Idle;
	m_tileMap = aTileMap;
	old_position = position;

	followTarget = false;
	m_pathFinder = new Pathfinder(m_tileMap, 10, 10);
	timer = 1;
	srand((unsigned int)time(0));
	targetPos = vec2((float)(rand() % 10)+1, (float)(rand() % 10)+1);

}

Enemy::~Enemy()
{
	delete m_pathFinder;
}

void Enemy::Update(float deltaTime)
{
	position += direction * 0.1f * deltaTime;
	
	if (timer <= 0)
	{
		MoveToNextNode();
		//if (followPath.size() > 0 && followTarget == true)
		{
			/*
			if (old_position.GetDistance(position) <= .01f)
			{
				vec2 nextNode = vec2((float)followPath[nextFollowNode].x, (float)followPath[nextFollowNode].y);
				position =nextNode;
				nextFollowNode++;
				if (nextFollowNode >= pathSize)
				{
					followTarget = false;
				}
				old_position = position;
			}
		}*/
		}
		timer = 1;
	}
		if (followPath.size() <= 0 || targetPos.GetDistance(position) < .1f)
		{
			targetPos = vec2((float)(rand() % 10) + 1, (float)(rand() % 10) + 1);
		}

	
	
		timer -= deltaTime;
}
vec2 Enemy::ConvertTileIndexToPosition(int index, int mapWidth)
{
	return vec2((float)(index % mapWidth), (float)(index / mapWidth));
	
}ivec2 Enemy::ConvertTileIndexToIntPosition(int index, int mapWidth)
{
	return ivec2((int)(index % mapWidth), (int)(index / mapWidth));
}

void Enemy::FindPath(ivec2 atargetPos)
{
	followPath.clear();

	if (m_pathFinder->FindPath((int)position.x, (int)position.y, atargetPos.x - 1, atargetPos.y - 1))
	{
		int path[255];
		pathSize = m_pathFinder->GetPath(path, 255, atargetPos.x - 1, atargetPos.y - 1);
		for (int i = pathSize - 1; i >= 0; i--)
		{
			followPath.push_back(ConvertTileIndexToIntPosition(path[i], m_tileMap->GetMapSize().x));
		}
		nextFollowNode = 0;
		followTarget = true;
	}
}
void Enemy::MoveToNextNode()
{
	if (m_pathFinder->FindPath((int)position.x, (int)position.y, (int)targetPos.x - 1, (int)targetPos.y - 1))
	{
		int path[255];
		pathSize = m_pathFinder->GetPath(path, 255, (int)targetPos.x - 1, (int)targetPos.y - 1);
		vec2 pos = (ConvertTileIndexToPosition(path[pathSize-2], m_tileMap->GetMapSize().x));
		position = pos;
		followTarget = true;
	}
}