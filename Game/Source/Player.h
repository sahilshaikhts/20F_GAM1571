#pragma once
#include"Framework.h"
class Player :public fw::GameObject
{
	fw::FWCore* frameWork;

public:
	Player(fw::GameCore* aCore);
	void Update(float deltaTime) override;

};

