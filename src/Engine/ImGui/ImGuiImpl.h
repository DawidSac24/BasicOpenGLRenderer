#pragma once

#include "Engine/Platform/OpenGL/Window.h"

namespace Gui
{
class ImGuiImpl
{
public:
    static void init(Core::Window& window);
    static void destroy();

    static void begin();
    static void end();

    static bool drawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
};
}
