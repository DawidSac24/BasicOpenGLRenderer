#pragma once

#include "Events/ApplicationEvents.h"
#include "Events/Event.h"

#include "Layer.h"
#include "Window.h"

#include <memory>
#include <string>
#include <vector>

namespace Core
{

// TODO:
// Add TransitionLayerEvent handling (idk if in this closs or another one yet)
// Add Renderer handling or initialisation ?
//  -- renderer should be allowed to have multiple instances so i initialise glfw ect here

struct ApplicationSpecification
{
    std::string applicationName = "application";
    Core::WindowSpecification windowSpec;
};

class Application
{
  private:
    ApplicationSpecification m_specification;
    std::shared_ptr<Window> m_window;
    bool m_isRunning = true;

    std::vector<std::unique_ptr<Layer>> m_layerStack;
    std::vector<Event::Event> m_pendingEvents;

  private:
    void flushEvents();

    bool onLayerTransition(Event::LayerTransitionEvent &event);

  public:
    Application(const ApplicationSpecification &appSpec = ApplicationSpecification());
    ~Application();

    void run();
    void stop();

    void raiseEvent(Event::Event &event);

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void pushLayer()
    {
        m_layerStack.push_back(std::make_unique<TLayer>());
    }

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    TLayer *getLayer()
    {
        for (const auto &layer : m_layerStack)
        {
            if (auto casted = dynamic_cast<TLayer *>(layer.get()))
                return casted;
        }
        return nullptr;
    }

    template <typename Event> void PushLayerTransition(Event event)
    {
        m_pendingEvents.push_back(std::move(event));
    }

    std::shared_ptr<Window> getWindow() const
    {
        return m_window;
    }

    static Application &get();
};
} // namespace Core
