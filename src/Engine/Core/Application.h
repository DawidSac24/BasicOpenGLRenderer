#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Engine/Core/ImGuiImpl.h"
#include "Engine/Scene.h"
#include "Events/Event.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Window.h"

namespace Core
{
struct ApplicationSpecification
{
    std::string applicationName = "application";
    Core::WindowSpecification windowSpec;
};

class Application
{
public:
    Application(const ApplicationSpecification& appSpec = ApplicationSpecification());
    ~Application();

    void run();
    void stop();

    void raiseEvent(Event& event);

    std::shared_ptr<Window> getWindow() const { return m_window; }
    std::shared_ptr<ImGuiImpl> getGui() const { return m_gui; }

    std::shared_ptr<Engine::Scene> getActiveScene() { return m_activeScene; }

    static Application& get();

    template <typename TLayer>
        requires(std::is_base_of_v<Layer, TLayer>)
    TLayer* getLayer()
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

    template <typename Event> void PushLayerTransition(Event event) { m_pendingEvents.push_back(std::move(event)); }

    void SetActiveScene(std::shared_ptr<Engine::Scene> newScene) { m_activeScene = newScene; }

private:
    ApplicationSpecification m_specification;

    std::shared_ptr<Window> m_window = nullptr;
    std::shared_ptr<ImGuiImpl> m_gui = nullptr;

    std::shared_ptr<Engine::Scene> m_activeScene = nullptr;

    bool m_isRunning = true;

    LayerStack m_layerStack;
    std::vector<Event> m_pendingEvents;

private:
    void flushEvents();
};
} // namespace Core
