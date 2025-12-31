#include "Application.h"

#include "Debug.h"
#include "Engine/Core/AssetManager.h"
#include "Engine/Events/ApplicationEvents.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Scene.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <ranges>

namespace Core
{
static Application* s_application = nullptr;

void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
}

Application::Application(const ApplicationSpecification& appSpec)
{
    s_application = this;

    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    if (m_specification.windowSpec.title.empty())
    {
        m_specification.windowSpec.title = m_specification.applicationName;
    }

    m_specification.windowSpec.eventCallback = [this](Event& event)
    { raiseEvent(event); };

    m_window = std::make_shared<Window>(m_specification.windowSpec);
    m_window->create();

    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "GLEW Init Failed: " << glewGetErrorString(err) << std::endl;
        throw std::runtime_error("Failed to initialize GLEW!");
    }

    Renderer::Renderer renderer;
    renderer.init();

    if (appSpec.windowSpec.enableOpenGLDebugInfo)
        Core::getOpenGLErrors();

    m_gui = std::make_shared<ImGuiImpl>(*m_window);

    m_activeScene = std::make_shared<Engine::Scene>("Default Scene");

    AssetManager::loadAssets();
}

Application::~Application()
{
    m_gui->destroy();
    m_window->destroy();
    glfwTerminate();

    s_application = nullptr;
}

void Application::run()
{
    m_isRunning = true;

    while (m_isRunning)
    {
        glfwPollEvents();

        if (m_window->shouldClose())
        {
            std::cout << "window should close !";
            stop();
            break;
        }

        for (const std::unique_ptr<Layer>& layer : m_layerStack)
            layer->onUpdate();

        for (const std::unique_ptr<Layer>& layer : m_layerStack)
        {
            layer->onRender();
            m_activeScene->onRender();
        }

        m_window->update();
        flushEvents();
    }
}

void Application::stop()
{
    m_isRunning = false;
}

void Application::raiseEvent(Event& event)
{
    for (auto& layer : std::views::reverse(m_layerStack))
    {
        layer->onEvent(event);
        if (event.handled)
            break;
    }
}

void Application::flushEvents()
{
    // Iterate through the generic event pointers
    for (auto& eventPtr : m_pendingEvents)
    {
        EventDispatcher dispatcher(eventPtr);
        dispatcher.dispatch<LayerTransitionEvent>(
            [this](LayerTransitionEvent& e)
            { return m_layerStack.onLayerTransition(e); });
        // might need to dispatch otter Events
    }

    m_pendingEvents.clear();
}

Application& Application::get()
{
    assert(s_application);
    return *s_application;
}

bool Application::onWindowResize(Core::WindowResizeEvent& e)
{
    if (e.getWidth() == 0 || e.getHeight() == 0)
        return false;

    Renderer::RenderCommand::setViewport(0, 0, e.getWidth(), e.getHeight());

    if (m_activeScene)
    {
        m_activeScene->updateCamerasViewport(e.getWidth(), e.getHeight());
    }

    return false;
}
} // namespace Core
