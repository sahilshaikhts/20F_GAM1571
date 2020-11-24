#include "GamePCH.h"
#include"Player.h"
#include "Objects/PlayerController.h"
#include"Events/GameEvents.h"

Player::Player(fw::GameCore* aCore,PlayerController* controller, std::string aName, char* spriteFName, vec4 aColor) :fw::GameObject(aCore, aName, aColor)
{
	lives = 3;
	speed = 5;
	radius = 0;
	position += vec2(1, 1);
	frameWork = aCore->GetFrameWork();
	m_controller = controller;
	nColor = color;
	flashRed=isSafe = false;
	invincibilityTimer = 0;
	
	m_spriteSheet = new fw::SpriteSheet(spriteFName);
	
	char* jsonText = fw::LoadCompleteFile(spriteFName, nullptr);
	rapidjson::Document doc;
	doc.Parse(jsonText);
	
	/*fw::Sprite* firstFrame = new fw::Sprite;
	firstFrame->UVOffset = vec2(doc["Sprites"]["LinkWalkRight1"]["X"].GetFloat()/256.0f, doc["Sprites"]["LinkWalkRight1"]["Y"].GetFloat()/128.0f);
	firstFrame->UVScale = vec2(doc["Sprites"]["LinkWalkRight1"]["W"].GetFloat()/256.0f, doc["LinkWalkRight1"]["H"].GetFloat()/128.0f);
	m_spriteSheet->AddSprite(firstFrame);*/


	m_spriteSheet->AddSprite("LinkWalkRight1");
	m_spriteSheet->AddSprite("LinkWalkRight2");
}

void Player::Update(float deltaTime)
{
	m_UVOffset = m_spriteSheet->GetCurrentFrameSprite()->UVOffset;
	m_UVScale = m_spriteSheet->GetCurrentFrameSprite()->UVScale;

	if (inputEnabled)
	{
		vec2 dir(0, 0);

		if (m_controller->IsHeld(PlayerController::Mask::Right))
		{
			dir.x = 1;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Left))
		{
			dir.x = -1;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Up))
		{
			dir.y = 1;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Down))
		{
			dir.y = -1;
		}

		position += dir * speed * deltaTime;
	}

	if (invincibilityTimer > 0)
	{
		invincibilityTimer -= deltaTime;
		if (invincibilityTimer <= 0)
			color.a =1;
	}
}

void Player::OnCollision(GameObject* other, fw::CollisionState aState)
{
	if (other->GetName() == "Enemy"|| other->GetName() == "Enemy_2" || other->GetName() == "Spike" && invincibilityTimer<=0) {
		if (aState == fw::CollisionState::Entered)
			if (lives > 1) {
				lives--;
				if(other->GetName() == "Enemy")
				m_Core->GetEventManager()->AddEvent(new RemoveFromGameEvent(other));
				invincibilityTimer = 1.5f;
				color.a = .5f;
			}
			else
			{
				m_Core->GetEventManager()->AddEvent(new GameStateChangeEvent(fw::GameState::Lost));
			}
	}
}




