#include "GamePCH.h"
#include"Player.h"
#include "Objects/PlayerController.h"
#include "../Data/Animations/Animation_Player.h"
#include"Events/GameEvents.h"

Player::Player(fw::GameCore* aCore, PlayerController* controller, std::string aName, vec4 aColor) :fw::GameObject(aCore, aName, aColor)
{
	lives = 3;
	speed = 4;
	radius = 0;
	position += vec2(1, 1);
	frameWork = aCore->GetFrameWork();
	m_controller = controller;
	nColor = color;
	flashRed = isSafe = false;
	invincibilityTimer = 0;

	m_animation = new Animation_Player("Data/Texture/Zelda.json");
	m_animState = AnimState::stop;
	currentSprite = m_animation->GetNextKeyFrame((Animation_Player::State)AnimState::down);

	animTimer = 0;
}
Player::~Player()
{
	delete m_animation;
}
void Player::Update(float deltaTime)
{
	if (currentSprite != nullptr) {
		m_UVScale = currentSprite->m_UVScale;
		m_UVOffset = currentSprite->m_UVOffset;
	}
	if (inputEnabled)
	{
		vec2 dir(0, 0);

		if (m_controller->IsHeld(PlayerController::Mask::Right))
		{
			dir.x = 1;
			m_animState = right;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Left))
		{
			dir.x = -1;
			m_animState = left;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Up))
		{
			dir.y = 1;
			m_animState = up;
		}

		if (m_controller->IsHeld(PlayerController::Mask::Down))
		{
			dir.y = -1;
			m_animState = down;
		}
		if (m_controller->IsHeld(PlayerController::Mask::Attack))
		{
		}
		if (m_animState != stop && animTimer>.15f)
		{
			currentSprite=m_animation->GetNextKeyFrame((Animation_Player::State)m_animState);
			animTimer = 0;
		}
		animTimer += deltaTime;
		position += dir * speed * deltaTime;
		m_animState = stop;
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




