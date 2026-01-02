#pragma once

#include "Engine/Core/UUID.h"
#include "Engine/Scene/EntityFactory.h"
#include "Entity.h"

#include <cstdint>
#include <list>
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
    std::list<Entity*>* getEntityList() { return &m_entityList; }

    Entity* createEntity(const std::string& p_name, EntityType type);
    void destroyEntity(Entity* obj);

    Entity* getPrimaryCamera() { return m_primaryCamera; }
    void setPrimaryCamera(Entity* targetEntity);
    void updateCamerasViewport(uint32_t width, uint32_t heigth);

private:
    std::unordered_map<Core::UUID, std::shared_ptr<Entity>> m_entityMap;
    std::list<Entity*> m_entityList;

    Entity* m_primaryCamera;

    EntityFactory m_entityFactory;
};
}
