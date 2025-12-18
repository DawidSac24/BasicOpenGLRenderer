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
    TLayer *getLayer()
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
    void pushLayer()
    {
        m_layers.push_back(std::make_unique<TLayer>());
    }

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void popLayer()
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

    bool onLayerTransition(LayerTransitionEvent &event);

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
