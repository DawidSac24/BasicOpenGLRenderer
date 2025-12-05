#pragma once

#include <functional>
#include <string>
namespace Core
{
enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

#define EVENT_CLASS_TYPE(type)                                                                                         \
    static EventType getStaticType()                                                                                   \
    {                                                                                                                  \
        return EventType::type;                                                                                        \
    }                                                                                                                  \
    virtual EventType getEventType() const override                                                                    \
    {                                                                                                                  \
        return getStaticType();                                                                                        \
    }                                                                                                                  \
    virtual const char *getName() const override                                                                       \
    {                                                                                                                  \
        return #type;                                                                                                  \
    }

class Event
{
  public:
    bool handled = false;

    virtual EventType getEventType() const = 0;
    virtual const char *getName() const = 0;
    virtual std::string toString() const
    {
        return getName();
    }
};

class EventDispatcher
{
    template <typename T> using EventFn = std::function<bool(T &)>;

  public:
    EventDispatcher(Event &event) : m_Event(event)
    {
    }

    template <typename T> bool Dispatch(EventFn<T> func)
    {
        if (m_Event.getEventType() == T::getStaticType() && !m_Event.handled)
        {
            m_Event.handled = func(*(T *)&m_Event);
            return true;
        }
        return false;
    }

  private:
    Event &m_Event;
};

} // namespace Core
