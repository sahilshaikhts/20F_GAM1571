#include "GamePCH.h"

#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{

}

void PlayerController::StartFrame()
{
	m_oldFlags = m_flags;
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
	fw::InputEvent* inputEvent = static_cast<fw::InputEvent*>(pEvent);

	if (inputEvent->GetDeviceType() == fw::InputEvent::InputDevice::keyboard)
	{
		if (inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::pressed) {
			if (inputEvent->GetKeyCode() == 'W')
				m_flags |= Up;
			if (inputEvent->GetKeyCode() == 'S')
				m_flags |= Down;
			if (inputEvent->GetKeyCode() == 'A')
				m_flags |= Left;
			if (inputEvent->GetKeyCode() == 'D')
				m_flags |= Right;
			if (inputEvent->GetKeyCode() == 32)
				m_flags |= Attack;
		}


		if (inputEvent->GetDeviceState() == fw::InputEvent::DeviceState::released) {
			if (inputEvent->GetKeyCode() == 'W')
				m_flags &= ~Up;
			if (inputEvent->GetKeyCode() == 'S')
				m_flags &= ~Down;
			if (inputEvent->GetKeyCode() == 'A')
				m_flags &= ~Left;
			if (inputEvent->GetKeyCode() == 'D')
				m_flags &= ~Right;
			if (inputEvent->GetKeyCode() == 32)
				m_flags &= ~Attack;
		}

	}
}
