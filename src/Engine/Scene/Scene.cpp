#include "Scene.h"

#include "Engine/Math/Transform.h"
#include "Entity.h"

#include "imgui.h"
#include <memory>

namespace Engine
{

Scene::Scene(const std::string& name)
    : name(name)
{
}

Entity* Scene::getEntityByUUID(Core::UUID uuid)
{
    auto it = m_entityMap.find(uuid);
    if (it != m_entityMap.end())
        return it->second.get();

    return nullptr;
}

Entity* Scene::createEntity(const std::string& p_name)
{
    std::shared_ptr<Entity> newObj = std::make_shared<Entity>(p_name);
    m_entityMap[newObj->getID()] = newObj;

    return newObj.get();
}
Entity* Scene::createEntity()
{
    std::shared_ptr<Entity> newObj = std::make_shared<Entity>();
    m_entityMap[newObj->getID()] = newObj;

    return newObj.get();
}

void Scene::destroyEntity(Entity* obj)
{
    if (!obj)
        return;

    m_entityMap.erase(obj->getID());
}
void Scene::destroyEntity(Core::UUID id)
{
    m_entityMap.erase(id);
}
}
