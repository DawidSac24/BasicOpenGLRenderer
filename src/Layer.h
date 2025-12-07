#pragma once

#include "Events/Event.h"
namespace Core
{
class Layer
{
  public:
    ~Layer() = default;

    virtual void onAttach();
    virtual void onUpdate();
    virtual bool onRender();

    virtual void onEvent(Event::Event &event);
};
} // namespace Core
