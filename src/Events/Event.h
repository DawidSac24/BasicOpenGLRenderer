#pragma once

#include <functional>
#include <string>
namespace Core
{
enum class EventType
{
    None = 0,
    // WindowEvents
    WindowClose,
    WindowResize,
    // KeyEvents
    KeyPressed,
    KeyReleased,
    // MouseEvents
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
    // ApplicationEvents
    LayerTransitionEvent,
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

    virtual ~Event() = default;

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
    EventDispatcher(Event &event) : m_event(event)
    {
    }

    template <typename T> bool dispatch(EventFn<T> func)
    {
        if (m_event.getEventType() == T::getStaticType() && !m_event.handled)
        {
            m_event.handled = func(*(T *)&m_event);
            return true;
        }
        return false;
    }

  private:
    Event &m_event;
};

} // namespace Core
