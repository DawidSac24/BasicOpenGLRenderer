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
    Scene(const std::string& name = "New Scene");
    void init();

    void onRender();

    void setName(const std::string& name) { this->name = name; }

    Entity* getEntityByUUID(Core::UUID uuid) const;
    std::unordered_map<Core::UUID, std::shared_ptr<Entity>>* getEntityMap() { return &m_entityMap; }
    std::list<Entity*>* getEntityList() { return &m_entityList; }

    bool addEntity(std::shared_ptr<Entity> entity);
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
