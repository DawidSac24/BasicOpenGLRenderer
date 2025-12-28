#pragma once

#include "Engine/Scene/Entity.h"

#include <memory>
#include <string>

namespace Engine
{
class EntityFactory
{
public:
    static std::unique_ptr<Entity> create(const std::string& name, EntityType type);

private:
    static std::unique_ptr<Entity> createEmpty(const std::string& name);

    static std::unique_ptr<Entity> createCamera(const std::string& name);

    static std::unique_ptr<Entity> createCube(const std::string& name);
    static std::unique_ptr<Entity> createSphere(const std::string& name);
    static std::unique_ptr<Entity> createPlane(const std::string& name);
};
}
