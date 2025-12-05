#pragma once

#include "Event.h"

#include <format>

namespace Event
{

class WindowClosedEvent : public Event
{
  public:
    WindowClosedEvent()
    {
    }

    EVENT_CLASS_TYPE(WindowClose)
};

class WindowResizeEvent : public Event
{
  private:
    uint32_t m_width, m_height;

  public:
    WindowResizeEvent(uint32_t width, uint32_t height) : m_width(width), m_height(height)
    {
    }

    inline uint32_t getWidth() const
    {
        return m_width;
    }
    inline uint32_t getHeight() const
    {
        return m_height;
    }

    std::string toString() const override
    {
        return std::format("WindowResizeEvent: {}, {}", m_width, m_height);
    }

    EVENT_CLASS_TYPE(WindowResize)
};
} // namespace Event
