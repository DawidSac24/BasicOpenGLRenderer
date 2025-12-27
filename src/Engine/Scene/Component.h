#pragma once

namespace Engine
{
class Entity;

class Component
{
public:
    virtual ~Component() = default;

    virtual void onUpdate(float deltaTime) { }

    virtual void onGuiRender() { }

    Entity* owner = nullptr;
};
}
