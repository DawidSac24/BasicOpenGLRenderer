#include "LayerStack.h"
#include <ranges>

namespace Core
{
LayerStack::LayerStack()
{
}

LayerStack::~LayerStack()
{
    for (auto &layer : std::ranges::views::reverse(m_layers))
    {
        layer->onDetach();
    }
}

bool LayerStack::onLayerTransition(LayerTransitionEvent &event)
{
    for (auto &layer : m_layers)
    {
        if (layer.get() == event.getOutgoingLayer())
        {
            layer = event.getIncomingLayer();
            return true;
        }
    }
    return false;
}

} // namespace Core
