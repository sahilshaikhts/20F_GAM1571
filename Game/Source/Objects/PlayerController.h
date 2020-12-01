#pragma once

class PlayerController
{
public:
    enum Mask {
        Up = 1,
        Down = 2,
        Left = 4,
        Right = 8,
        Attack=16,
    };
    PlayerController();
    virtual ~PlayerController();

    void StartFrame();
    void OnEvent(fw::Event* pEvent);

    bool IsHeld(Mask dir) { return (m_flags & dir) != 0; }

    bool WasPressed(Mask dir) { return(((m_oldFlags & dir) != 0) && ((m_flags & dir) == 0)); }
    bool WasReleased(Mask dir) { return(((m_oldFlags & dir) != 0) && ((m_flags & dir) == 0)); }
   
protected:
    unsigned int m_flags = 0;
    unsigned int m_oldFlags = 0;
};
