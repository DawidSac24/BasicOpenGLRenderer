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

template <typename TLayer>
    requires(std::is_base_of_v<Layer, TLayer>)
TLayer *LayerStack::getLayer()
{
    for (const auto &layer : m_layers)
    {
        if (auto casted = dynamic_cast<TLayer *>(layer.get()))
            return casted;
    }
    return nullptr;
}

template <typename TLayer>
    requires(std::is_base_of_v<Layer, TLayer>)
void LayerStack::pushLayer()
{
    m_layers.push_back(std::make_unique<TLayer>());
}

template <typename TLayer>
    requires(std::is_base_of_v<Layer, TLayer>)
void LayerStack::popLayer()
{
    auto layer = std::ranges::find_if(m_layers.begin(), m_layers.end(), [](const std::unique_ptr<Layer> &layer) {
        return dynamic_cast<TLayer *>(layer.get()) != nullptr;
    });

    if (layer != m_layers.end())
    {
        (*layer)->onDetach();

        m_layers.erase(layer);
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
