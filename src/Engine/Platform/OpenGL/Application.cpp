#include "Application.h"

#include "Debug.h"
#include "Engine/Core/AssetManager.h"
#include "Engine/Core/Events/ApplicationEvents.h"
#include "Engine/Core/Events/Event.h"
#include "Engine/Core/Events/WindowEvents.h"
#include "Engine/Core/Log.h"
#include "Engine/ImGui/ImGuiImpl.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Scene.h"

#include <cassert>
#include <memory>
#include <ranges>

namespace Core
{
static Application* s_application = nullptr;

void glfwErrorCallback(int error, const char* description)
{
    CORE_ERROR("GLFW Error ({}): {}", error, description);
}

Application::Application(const ApplicationSpecification& appSpec)
{
    s_application = this;

    Log::init();

    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        CORE_CRITICAL("Failed to initialize GLFW");
        return;
    }

    if (m_specification.windowSpec.title.empty())
    {
        m_specification.windowSpec.title = m_specification.applicationName;
    }

    m_specification.windowSpec.eventCallback = [this](Event& event)
    {
        raiseEvent(event);
    };

    m_window = std::make_shared<Window>(m_specification.windowSpec);
    m_window->create();

    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        const char* errorString = (const char*)glewGetErrorString(err);
        CORE_CRITICAL("GLEW Init Failed: {}", errorString);
        return;
    }

    Renderer::Renderer renderer;
    renderer.init();

    if (appSpec.windowSpec.enableOpenGLDebugInfo)
        Core::getOpenGLErrors();

    Gui::ImGuiImpl::init(*m_window);

    m_activeScene = std::make_shared<Engine::Scene>("Default Scene");

    AssetManager::loadAssets();
    CORE_INFO("Application Initialized");
}

Application::~Application()
{
    Gui::ImGuiImpl::destroy();
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
            CORE_INFO("window should close !");
            stop();
            break;
        }

        for (const std::unique_ptr<Layer>& layer : m_layerStack)
            layer->onUpdate();

        for (const std::unique_ptr<Layer>& layer : m_layerStack)
        {
            layer->onRender();
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
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent& e)
    {
        return onWindowResize(e);
    });
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
        {
            return m_layerStack.onLayerTransition(e);
        });
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
