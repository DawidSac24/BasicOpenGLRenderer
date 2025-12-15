#include "Window.h"

#include <GLFW/glfw3.h>
#include <cassert>
#include <iostream>

#include "Events/InputEvents.h"
#include "Events/WindowEvents.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
    // gladLoadGL(glfwGetProcAddress);

    glfwSwapInterval(m_specification.VSync ? 1 : 0);

    glfwSetWindowUserPointer(m_handle, this);

    glfwSetWindowCloseCallback(m_handle, [](GLFWwindow *handle) {
        Window &window = *((Window *)glfwGetWindowUserPointer(handle));

        Event::WindowClosedEvent(event);
        window.raiseEvent(event);
    });

    glfwSetWindowSizeCallback(m_handle, [](GLFWwindow *handle, int width, int height) {
        Window &window = *((Window *)glfwGetWindowUserPointer(handle));

        Event::WindowResizeEvent event((uint32_t)width, (uint32_t)height);
        window.raiseEvent(event);
    });

    glfwSetKeyCallback(m_handle, [](GLFWwindow *handle, int key, int scancode, int action, int mods) {
        Window &window = *((Window *)glfwGetWindowUserPointer(handle));

        switch (action)
        {
        case GLFW_PRESS:
        case GLFW_REPEAT: {
            Event::KeyPressedEvent event(key, action == GLFW_REPEAT);
            window.raiseEvent(event);
            break;
        }
        case GLFW_RELEASE: {
            Event::KeyReleasedEvent event(key);
            window.raiseEvent(event);
            break;
        }
        }
    });

    glfwSetMouseButtonCallback(m_handle, [](GLFWwindow *handle, int button, int action, int mods) {
        Window &window = *((Window *)glfwGetWindowUserPointer(handle));

        switch (action)
        {
        case GLFW_PRESS: {
            Event::MouseButtonPressedEvent event(button);
            window.raiseEvent(event);
            break;
        }
        case GLFW_RELEASE: {
            Event::MouseButtonReleasedEvent event(button);
            window.raiseEvent(event);
            break;
        }
        }
    });

    glfwSetScrollCallback(m_handle, [](GLFWwindow *handle, double xOffset, double yOffset) {
        Window &window = *((Window *)glfwGetWindowUserPointer(handle));

        Event::MouseScrolledEvent event(xOffset, yOffset);
        window.raiseEvent(event);
    });

    glfwSetCursorPosCallback(m_handle, [](GLFWwindow *handle, double x, double y) {
        Window &window = *((Window *)glfwGetWindowUserPointer(handle));

        Event::MouseMovedEvent event(x, y);
        window.raiseEvent(event);
    });
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

void Window::raiseEvent(Event::Event &event)
{
    if (m_specification.eventCallback)
        m_specification.eventCallback(event);
}

glm::vec2 Window::getFrameBufferSize() const
{
    int width, height;
    glfwGetFramebufferSize(m_handle, &width, &height);
    return {width, height};
}

glm::vec2 Window::getMousePos() const
{
    double x, y;
    glfwGetCursorPos(m_handle, &x, &y);
    return {static_cast<float>(x), static_cast<float>(y)};
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_handle);
}
} // namespace Core
