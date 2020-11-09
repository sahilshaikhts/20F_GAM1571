    #pragma once
namespace fw {

    class Event
    {
    public:
        Event();
        virtual ~Event();
        virtual const char* GetType() = 0;
    };

    

    class InputEvent :public Event
    {
    public:
        enum class InputDevice
        {
            keyboard,
        };
        enum class DeviceState
        {
            pressed,
            released,
        };

   
        InputEvent(InputDevice pDevice, DeviceState pState,unsigned int keyCode)
        {
            m_device = pDevice;
            m_state = pState;
            m_KeyCode = keyCode;
        }
        virtual ~InputEvent() {}

        static const char* GetStaticEventType() { return "InputEvent"; }
        virtual const char* GetType() override { return GetStaticEventType(); }

        InputDevice GetDeviceType() { return m_device; }
        DeviceState GetDeviceState() { return m_state; }
        unsigned int GetKeyCode(){ return m_KeyCode; }

    protected:
        InputDevice m_device;
        DeviceState m_state;
        unsigned int m_KeyCode;

    };
}