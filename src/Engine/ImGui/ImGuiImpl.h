#pragma once

#include "Engine/Platform/OpenGL/Window.h"

namespace Core
{
class ImGuiImpl
{
public:
    ImGuiImpl(Window& window);
    ~ImGuiImpl();
    void destroy();

    void newFrame();
    void draw();

private:
    Window* m_window;
};
}
