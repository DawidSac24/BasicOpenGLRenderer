#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <functional>
#include <string>

#include <Events/Event.h>

namespace Core
{

struct WindowSpecification
{
    std::string title;
    uint32_t width = 1280;
    uint32_t height = 720;
    bool isResizeable = true;
    bool VSync = true;
    bool isInDEbugMode = false;

    using EventCallbackFn = std::function<void(Event::Event &)>;
    EventCallbackFn eventCallback;
};

class Window
{
  private:
    WindowSpecification m_specification;

    GLFWwindow *m_handle = nullptr;

  public:
    Window(const WindowSpecification &specification);

    ~Window();

    void create();
    void destroy();

    void update();

    void raiseEvent(Event::Event &event);

    glm::vec2 getFrameBufferSize() const;
    glm::vec2 getMousePos() const;

    bool shouldClose() const;

    GLFWwindow *getHandle() const
    {
        return m_handle;
    }
};
} // namespace Core
