#pragma once

#include "Events/ApplicationEvents.h"
#include "Layer.h"
#include <memory>
#include <vector>

namespace Core
{
class LayerStack
{
  private:
    std::vector<std::unique_ptr<Layer>> m_layers;

  public:
    LayerStack();
    ~LayerStack();

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    TLayer *getLayer();

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void pushLayer();
    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void popLayer();

    bool onLayerTransition(Event::LayerTransitionEvent &event);

    using iterator = std::vector<std::unique_ptr<Layer>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<Layer>>::const_iterator;
    using reverse_iterator = std::vector<std::unique_ptr<Layer>>::reverse_iterator;
    using const_reverse_iterator = std::vector<std::unique_ptr<Layer>>::const_reverse_iterator;

    iterator begin()
    {
        return m_layers.begin();
    }
    iterator end()
    {
        return m_layers.end();
    }
    reverse_iterator rbegin()
    {
        return m_layers.rbegin();
    }
    reverse_iterator rend()
    {
        return m_layers.rend();
    }

    const_iterator begin() const
    {
        return m_layers.begin();
    }
    const_iterator end() const
    {
        return m_layers.end();
    }
    const_reverse_iterator rbegin() const
    {
        return m_layers.rbegin();
    }
    const_reverse_iterator rend() const
    {
        return m_layers.rend();
    }
};
} // namespace Core
