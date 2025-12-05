#pragma once

#include "Event.h"

#include <format>

namespace Event
{

//
// Key Events
//

class KeyEvent : public Event
{
  protected:
    KeyEvent(int keycode) : m_keyCode(keycode)
    {
    }

    int m_keyCode;

  public:
    inline int getKeyCode() const
    {
        return m_keyCode;
    }
};

class KeyPressedEvent : public KeyEvent
{
  private:
    bool m_isRepeat;

  public:
    KeyPressedEvent(int keycode, bool isRepeat) : KeyEvent(keycode), m_isRepeat(isRepeat)
    {
    }

    inline bool isRepeat() const
    {
        return m_isRepeat;
    }

    std::string toString() const override
    {
        return std::format("KeyPressedEvent: {} (repeat={})", m_keyCode, m_isRepeat);
    }

    EVENT_CLASS_TYPE(KeyPressed)
};

class KeyReleasedEvent : public KeyEvent
{
  public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode)
    {
    }

    std::string toString() const override
    {
        return std::format("KeyReleasedEvent: {}", m_keyCode);
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

//
// Mouse Events
//

class MouseMovedEvent : public Event
{
  private:
    double m_mouseX, m_mouseY;

  public:
    MouseMovedEvent(double x, double y) : m_mouseX(x), m_mouseY(y)
    {
    }

    inline double getX() const
    {
        return m_mouseX;
    }
    inline double getY() const
    {
        return m_mouseY;
    }

    std::string toString() const override
    {
        return std::format("MouseMovedEvent: {}, {}", m_mouseX, m_mouseY);
    }

    EVENT_CLASS_TYPE(MouseMoved)
};

class MouseScrolledEvent : public Event
{
  private:
    double m_xOffset, m_yOffset;

  public:
    MouseScrolledEvent(double xOffset, double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset)
    {
    }

    inline double getXOffset() const
    {
        return m_xOffset;
    }
    inline double getYOffset() const
    {
        return m_yOffset;
    }

    std::string toString() const override
    {
        return std::format("MouseScrolledEvent: {}, {}", m_xOffset, m_yOffset);
    }

    EVENT_CLASS_TYPE(MouseScrolled)
};

class MouseButtonEvent : public Event
{
  protected:
    MouseButtonEvent(int button) : m_button(button)
    {
    }

    int m_button;

  public:
    inline int GetMouseButton() const
    {
        return m_button;
    }
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
  public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button)
    {
    }

    std::string toString() const override
    {
        return std::format("MouseButtonPressedEvent: {}", m_button);
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
  public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button)
    {
    }

    std::string toString() const override
    {
        return std::format("MouseButtonReleasedEvent: {}", m_button);
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

} // namespace Event
