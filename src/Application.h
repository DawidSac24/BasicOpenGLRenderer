#pragma once

#include "Events/ApplicationEvents.h"
#include "Events/Event.h"

#include "Layer.h"
#include "LayerStack.h"
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

    LayerStack m_layerStack;
    std::vector<Event> m_pendingEvents;

  private:
    void flushEvents();

  public:
    Application(const ApplicationSpecification &appSpec = ApplicationSpecification());
    ~Application();

    void run();
    void stop();

    void raiseEvent(Event &event);

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    TLayer *getLayer()
    {
        return m_layerStack.getLayer<TLayer>();
    }
    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void pushLayer()
    {
        m_layerStack.pushLayer<TLayer>();
    }
    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    void popLayer()
    {
        m_layerStack.popLayer<TLayer>();
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
