#pragma once
#include"Framework.h"
#include "Objects/GameObject.h"
class Player :public fw::GameObject
{
	fw::FWCore* frameWork;
	float previousTime;
public:
	Player(fw::FWCore* aCore);
	void Update();

};

