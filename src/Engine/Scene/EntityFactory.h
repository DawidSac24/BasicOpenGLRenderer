#pragma once

#include "Engine/Scene/Entity.h"

#include <memory>
#include <string>

namespace Engine
{
class EntityFactory
{
public:
    EntityFactory(Scene* scene)
        : m_scene(scene)
    {
    }

    std::unique_ptr<Entity> create(const std::string& name, EntityType type);

private:
    Scene* m_scene;

private:
    std::unique_ptr<Entity> createPrimitiveEntity(const std::string& name, EntityType type);

    std::unique_ptr<Entity> createCamera(const std::string& name);
};
}
