#include "Engine/Scene.h"
#include "Engine/GameObject.h"
#include <memory>

namespace Engine
{

Scene::Scene(const std::string& name)
    : name(name)
{
}

GameObject* Scene::getGameObjectByUUID(Core::UUID uuid)
{
    auto it = m_entityMap.find(uuid);
    if (it != m_entityMap.end())
        return it->second.get();

    return nullptr;
}

GameObject* Scene::createGameObject(const std::string& p_name)
{
    std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>(p_name);
    m_entityMap[newObj->getID()] = newObj;

    return newObj.get();
}
GameObject* Scene::createGameObject()
{
    std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>();
    m_entityMap[newObj->getID()] = newObj;

    return newObj.get();
}

void Scene::destroyGameObject(GameObject* obj)
{
    if (!obj)
        return;

    m_entityMap.erase(obj->getID());
}

void Scene::destroyGameObject(Core::UUID id)
{
    m_entityMap.erase(id);
}
}
