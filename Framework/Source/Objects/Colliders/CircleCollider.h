#pragma once
#include "Math/Vector.h"
namespace fw {
	class GameObject;
	class CircleCollider {
		CircleCollider(GameObject* obj,float aRadius);
		virtual void Update(float deltaTime);

	private:
		GameObject* parent;
		vec2 position;
		float radius;
	};
}