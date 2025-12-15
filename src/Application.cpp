#include "Debug.h"
#include "Events/ApplicationEvents.h"
#include "Events/Event.h"

#include "Application.h"
#include <cassert>
#include <memory>
#include <ranges>

namespace Core
{
static Application *s_application = nullptr;

Application::Application(const ApplicationSpecification &appSpec)
{
    s_application = this;

    glfwInit();

    if (m_specification.windowSpec.title.empty())
    {
        m_specification.windowSpec.title = m_specification.applicationName;
    }

    m_specification.windowSpec.eventCallback = [this](Event &event) { raiseEvent(event); };

    m_window = std::make_shared<Window>(m_specification.windowSpec);
    m_window->create();

    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    Core::getOpenGLErrors();
}

Application::~Application()
{
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
            stop();
            break;
        }

        for (const std::unique_ptr<Layer> &layer : m_layerStack)
            layer->onUpdate();

        for (const std::unique_ptr<Layer> &layer : m_layerStack)
            layer->onRender();

        m_window->update();
        flushEvents();
    }
}

void Application::stop()
{
    m_isRunning = false;
}

void Application::raiseEvent(Event &event)
{
    for (auto &layer : std::views::reverse(m_layerStack))
    {
        layer->onEvent(event);
        if (event.handled)
            break;
    }
}

void Application::flushEvents()
{
    // Iterate through the generic event pointers
    for (auto &eventPtr : m_pendingEvents)
    {
        EventDispatcher dispatcher(eventPtr);
        dispatcher.dispatch<LayerTransitionEvent>(
            [this](LayerTransitionEvent &e) { return m_layerStack.onLayerTransition(e); });
        // might need to dispatch otter Events
    }

    m_pendingEvents.clear();
}

Application &Application::get()
{
    assert(s_application);
    return *s_application;
}
} // namespace Core
