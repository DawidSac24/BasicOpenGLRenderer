#pragma once

#include "Engine/Core/Layer.h"

#include <memory>

namespace Core
{
class LayerTransitionEvent : public Event
{
  private:
    Core::Layer *outgoingLayer;
    std::unique_ptr<Core::Layer> incomingLayer;

  public:
    LayerTransitionEvent(Core::Layer *outgoinglayer, std::unique_ptr<Core::Layer> incomingLayer)
        : outgoingLayer(outgoinglayer), incomingLayer(std::move(incomingLayer))
    {
    }

    Core::Layer *getOutgoingLayer()
    {
        return outgoingLayer;
    }

    // [[nodiscard]] to warn if we take ownership but don't save it
    [[nodiscard]] std::unique_ptr<Core::Layer> getIncomingLayer()
    {
        return std::move(incomingLayer);
    }

    EVENT_CLASS_TYPE(LayerTransitionEvent)
};
} // namespace Core
