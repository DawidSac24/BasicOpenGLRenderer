#pragma once

#include <GLFW/glfw3.h>

#include <cstdint>
#include <string>

namespace Core
{

struct WindowSpecification
{
    std::string title;
    uint32_t width = 1280;
    uint32_t height = 720;
    bool isResizeable = true;
    bool isInDEbugMode = false;
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

    bool shouldClose() const;

    GLFWwindow *getHandle() const
    {
        return m_handle;
    }
};
} // namespace Core
