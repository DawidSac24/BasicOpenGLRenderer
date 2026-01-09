#pragma once

#include "Engine/Scene/Components/Component.h"

namespace Engine
{
class ScriptComponent : Component
{
public:
    ScriptComponent(Entity* owner)
        : Component(owner) { };

    virtual void onSetup() = 0;

    virtual void onUpdate(float deltaTime) = 0;
};
}
