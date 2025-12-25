#include "Application.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <ranges>

#include "Debug.h"
#include "Events/ApplicationEvents.h"
#include "Events/Event.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

namespace Core
{
static Application* s_application = nullptr;

Application::Application(const ApplicationSpecification& appSpec)
{
    s_application = this;

    glfwInit();

    if (m_specification.windowSpec.title.empty())
    {
        m_specification.windowSpec.title = m_specification.applicationName;
    }

    m_specification.windowSpec.eventCallback = [this](Event& event) { raiseEvent(event); };

    m_window = std::make_shared<Window>(m_specification.windowSpec);
    m_window->create();

    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    // ImGUI initialisation
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale); // Bake a fixed style scale. (until we have a solution for
                                     // dynamic style scaling, changing this requires resetting
                                     // Style + calling this again)
    style.FontScaleDpi = main_scale; // Set initial font scale. (using io.ConfigDpiScaleFonts=true
                                     // makes this unnecessary. We leave both here for
                                     // documentation purpose)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window->getHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    Core::getOpenGLErrors();
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (const std::unique_ptr<Layer>& layer : m_layerStack)
            layer->onUpdate();

        for (const std::unique_ptr<Layer>& layer : m_layerStack)
            layer->onRender();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
            [this](LayerTransitionEvent& e) { return m_layerStack.onLayerTransition(e); });
        // might need to dispatch otter Events
    }

    m_pendingEvents.clear();
}

Application& Application::get()
{
    assert(s_application);
    return *s_application;
}
} // namespace Core
