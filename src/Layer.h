#pragma once

#include "Events/Event.h"
namespace Core
{
class Layer
{
  public:
    ~Layer() = default;

    virtual void onEvent(Event::Event &event);

    virtual void onUpdate();
    virtual bool onRender();
};
} // namespace Core
