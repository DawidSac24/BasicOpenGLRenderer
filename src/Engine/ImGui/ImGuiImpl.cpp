#include "ImGuiImpl.h"
#include "Engine/Platform/OpenGL/Application.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

namespace Core
{
ImGuiImpl::ImGuiImpl(Window& window)
    : m_window(&window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Essential for Engine Tools!
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Drag windows outside main app

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    // 'true' installs GLFW callbacks. Ensure this is called AFTER Window creation.
    ImGui_ImplGlfw_InitForOpenGL(m_window->getHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

ImGuiImpl::~ImGuiImpl()
{
    destroy();
}

void ImGuiImpl::destroy()
{
    // Safety check to prevent crashing if called multiple times
    if (ImGui::GetCurrentContext())
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

void ImGuiImpl::begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiImpl::end()
{
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::get();

    // REMOVED: Manual io.DisplaySize setting.
    // ImGui_ImplGlfw_NewFrame handles this automatically and handles High-DPI better.

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
}
