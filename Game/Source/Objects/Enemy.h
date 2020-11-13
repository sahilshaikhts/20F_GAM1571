#pragma once
class Player;
class Enemy :public fw::GameObject
{
private:
	Player* player;
	vec2 direction;
	int hp;
	vec2 boundsCenter;
	float boundsRadius, radius;
	fw::CollisionState  collisionState;
public:
	float speed;
	bool physicalCollider=false;
	Enemy(fw::GameCore* core,Player* aPlayer,vec2 startPosition, vec2 aDir,vec4 aColor, fw::Mesh* aMesh,vec2 aBoundsCenter,float aBoundsRadius,float aRadius);
	~Enemy();
	void Update(float deltaTime) override;

};

