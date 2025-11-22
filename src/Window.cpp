#include "Window.h"

#include <GLFW/glfw3.h>

#include <cassert>
#include <iostream>

namespace Core
{
Window::Window(const WindowSpecification &specification) : m_specification(specification)
{
}

Window::~Window()
{
    destroy();
}

void Window::create()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, m_specification.isInDEbugMode);

    m_handle = glfwCreateWindow(m_specification.width, m_specification.height, m_specification.title.c_str(), nullptr,
                                nullptr);
    if (!m_handle)
    {
        std::cerr << "Failed to create Window !\n";
        assert(false);
    }

    glfwMakeContextCurrent(m_handle);
}

void Window::destroy()
{
    if (m_handle)
    {
        glfwDestroyWindow(m_handle);
    }
    m_handle = nullptr;
}

void Window::update()
{
    glfwSwapBuffers(m_handle);
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_handle);
}
} // namespace Core
