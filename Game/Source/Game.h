#pragma once
class Game: public fw::GameCore
{
public:
	virtual ~Game();
	virtual void Update() override;
	virtual void Draw() override;
};
