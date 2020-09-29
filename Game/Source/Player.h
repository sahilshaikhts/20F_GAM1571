#pragma once
#include"Framework.h"
#include "Objects/GameObject.h"
class Player :public fw::GameObject
{
	fw::GameCore* frameWork;

public:
	Player(fw::GameCore* aCore);
	void Draw();
	void Update();

};

