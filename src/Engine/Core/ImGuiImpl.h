#pragma once

#include "Engine/Core/Window.h"
#include <memory>
#include <string>

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
