#pragma once

#include "Engine/Scene/Entity.h"
#include <string>
namespace Engine
{
class EntityFactory
{
public:
    EntityFactory();

    Entity* createEntity(EntityType type, std::string* name);

private:
    Entity* createEmptyEntity(std::string* name);
    Entity* createCubeEntity(std::string* name);
    Entity* createSphereEntity(std::string* name);
};
}
