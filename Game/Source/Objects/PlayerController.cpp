#include "GamePCH.h"

#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::OnEvent(fw::Event* pEvent)
{
    if( pEvent->GetType() == fw::InputEvent::GetStaticEventType() )
    {
        fw::InputEvent* pInputEvent = static_cast<fw::InputEvent*>( pEvent );
        
        if( pInputEvent->GetDeviceType() == fw::InputEvent::DeviceType::Keyboard )
        {
            if( pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Pressed )
            {
                if( pInputEvent->GetKeyCode() == 'W' ) { m_Up = true; }
                if( pInputEvent->GetKeyCode() == 'S' ) { m_Down = true; }
                if( pInputEvent->GetKeyCode() == 'A' ) { m_Left = true; }
                if( pInputEvent->GetKeyCode() == 'D' ) { m_Right = true; }
            }

            if( pInputEvent->GetDeviceState() == fw::InputEvent::DeviceState::Released )
            {
                if( pInputEvent->GetKeyCode() == 'W' ) { m_Up = false; }
                if( pInputEvent->GetKeyCode() == 'S' ) { m_Down = false; }
                if( pInputEvent->GetKeyCode() == 'A' ) { m_Left = false; }
                if( pInputEvent->GetKeyCode() == 'D' ) { m_Right = false; }
            }
        }
    }
}
