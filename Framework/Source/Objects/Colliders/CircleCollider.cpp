#include"FrameworkPCH.h"
#include"CircleCollider.h"
#include"Objects/GameObject.h"
namespace fw {		//UNDER PROGRESS
	CircleCollider::CircleCollider(GameObject* obj, float aRadius)
	{
		parent = obj;
		radius = aRadius;
	}
	void CircleCollider::Update(float deltaTime)
	{
		
	}
}