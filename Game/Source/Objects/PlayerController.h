#pragma once

class PlayerController
{
public:
    PlayerController();
    virtual ~PlayerController();

    void OnEvent(fw::Event* pEvent);

    bool IsUpHeld()     { return m_Up; }
    bool IsDownHeld()   { return m_Down; }
    bool IsLeftHeld()   { return m_Left; }
    bool IsRightHeld()  { return m_Right; }

protected:
    bool m_Up = false;
    bool m_Down = false;
    bool m_Left = false;
    bool m_Right = false;
};
