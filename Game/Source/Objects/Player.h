#pragma once
class Player :public fw::GameObject
{
	fw::FWCore* frameWork;
	float speed;

public:
	Player(fw::GameCore* aCore, std::string aName,vec4 aColor);
	void Update(float deltaTime) override;

};

