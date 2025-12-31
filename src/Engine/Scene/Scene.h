#pragma once

#include "Engine/Core/UUID.h"
#include "Entity.h"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

namespace Engine
{
class Entity;
class CameraComponent;
enum class EntityType;

class Scene
{
public:
    std::string name;

public:
    Scene(const std::string& name);

    void onRender();

    Entity* getEntityByUUID(Core::UUID uuid);
    std::unordered_map<Core::UUID, std::shared_ptr<Entity>>* getEntityMap() { return &m_entityMap; }

    Entity* createEntity(const std::string& p_name, EntityType type);
    void destroyEntity(Entity* obj);
    void destroyEntity(Core::UUID id);

    void updateCamerasViewport(uint32_t width, uint32_t heigth);

private:
    std::unordered_map<Core::UUID, std::shared_ptr<Entity>> m_entityMap;
};
}
