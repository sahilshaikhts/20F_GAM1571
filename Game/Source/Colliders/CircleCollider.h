#pragma once
#include"Collider.h"
class CircleCollider:public Collider
{
private:
	float radius;
public:
	CircleCollider(fw::GameObject* aParentObject, fw::EventManager* aEventManager, float aRadius, fw::vec2 aOffset);
	void Update(float deltaTime) override;
};

