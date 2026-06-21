#pragma once

namespace Engine
{
class Entity;

class Component
{
public:
    Component(Entity* owner)
        : owner(owner)
    {
    }
    virtual ~Component() = default;

    virtual void onUpdate(float /*deltaTime*/) { }

    virtual void onRender() { }

    Entity* owner = nullptr;
};
}
