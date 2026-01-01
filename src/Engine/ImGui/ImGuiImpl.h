#pragma once

#include "Engine/Platform/OpenGL/Window.h"

namespace Gui
{
class ImGuiImpl
{
public:
    ImGuiImpl(Core::Window& window);
    ~ImGuiImpl();
    void destroy();

    void begin();
    void end();

private:
    Core::Window* m_window;
};
}
