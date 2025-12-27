#pragma once

#include "Engine/Core/UUID.h"
#include "Entity.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace Engine
{
class Scene
{
public:
    std::string name;

public:
    Scene(const std::string& name);

    Entity* getEntityByUUID(Core::UUID uuid);
    std::unordered_map<Core::UUID, std::shared_ptr<Entity>>* getEntityMap() { return &m_entityMap; }

    Entity* createEntity(const std::string* p_name);
    void destroyEntity(Entity* obj);
    void destroyEntity(Core::UUID id);

private:
    std::unordered_map<Core::UUID, std::shared_ptr<Entity>> m_entityMap;
};
}
