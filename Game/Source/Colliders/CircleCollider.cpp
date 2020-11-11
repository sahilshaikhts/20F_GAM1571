#include "GamePCH.h"
#include "Objects/PlayerController.h"
#include"Events/GameEvents.h"
CircleCollider::CircleCollider(fw::GameObject* aParentObject,fw::EventManager* aEventManager, float aRadius,vec2 aOffset)
{
	Collider::allColliders.push_back(this);

	eventManager = aEventManager;
	shape = ColliderShape::circle;
	parentObject = aParentObject;
	offset = aOffset;
	radius = aRadius;
}

void CircleCollider::Update(float deltaTime)
{
	position = parentObject->position + offset;

	for (auto it = Collider::allColliders.begin(); it != Collider::allColliders.end(); it++)
	{
		 
		if ((*it)->shape == ColliderShape::circle)
		{
			CircleCollider* otherCollider = static_cast<CircleCollider*>((*it));

			auto target= std::find(collidingObjects.begin(), collidingObjects.end(), (*it));
			if (position.GetDistance(otherCollider->position) < radius + otherCollider->radius)
			{
				
				if ( target!= collidingObjects.end())	//already not collided i.e not in the list
				{
					eventManager->AddEvent(new CollisionEvent(parentObject, otherCollider->parentObject, CollisionState::Entered));
					collidingObjects.push_back((*it));
				}
				else
				{
					eventManager->AddEvent(new CollisionEvent(parentObject, otherCollider->parentObject, CollisionState::Colliding));
				}
			}
			else
			{
			std::remove(collidingObjects.begin(), collidingObjects.end(), (*target));
				eventManager->AddEvent(new CollisionEvent(parentObject, otherCollider->parentObject, CollisionState::Exited));
			}
		}
	}
}





