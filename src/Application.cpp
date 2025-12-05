#include "Debug.h"

#include "Application.h"
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
    }
}

void Application::stop()
{
    m_isRunning = false;
}

void Application::raiseEvent(Event::Event &event)
{
    for (auto &layer : std::views::reverse(m_layerStack))
    {
        layer->onEvent(event);
        if (event.handled)
            break;
    }
}

Application &Application::get()
{
    assert(s_application);
    return *s_application;
}
} // namespace Core
