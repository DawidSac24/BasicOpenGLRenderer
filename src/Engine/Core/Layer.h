#pragma once

#include "Engine/Events/Event.h"

namespace Core
{
class Layer
{
public:
    virtual ~Layer() = default;

    virtual void onUpdate() { }

    virtual void onRender() { }

    virtual void onEvent(Event& event) { }

    virtual void onDetach() { }
};
} // namespace Core
