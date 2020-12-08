#pragma once
class Player;
class Pathfinder;
class TileMap;
class Enemy :public fw::GameObject
{
private:
	Player* player;
	vec2 direction,old_position;
	vec2 targetPos;
	int hp,nextFollowNode=0,pathSize;
	std::vector<ivec2> followPath;
;	fw::CollisionState  collisionState;
	fw::SpriteSheet* m_spriteSheet=nullptr;
	Pathfinder* m_pathFinder= nullptr;
	TileMap* m_tileMap= nullptr;

	bool followTarget = false;
	
	vec2 ConvertTileIndexToPosition(int index, int mapWidth);
	ivec2 ConvertTileIndexToIntPosition(int index, int mapWidth);
	void FindPath(ivec2 targetPos);
	void MoveToNextNode();
public:
	float dist;//temp
	float speed,timer=1;
	bool physicalCollider=false;
	Enemy(fw::GameCore* core,TileMap* aTileMap,Player* aPlayer, fw::SpriteSheet* aSpriteSheet,vec2 startPosition,vec4 aColor, fw::Mesh* aMesh);
	~Enemy();
	void Update(float deltaTime) override;
};

