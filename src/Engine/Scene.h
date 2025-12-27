#pragma once

#include "Core/UUID.h"
#include "Objects/GameObject.h"

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

    void onGuiRender();

    GameObject* getGameObjectByUUID(Core::UUID uuid);

    GameObject* createGameObject(const std::string& p_name);
    GameObject* createGameObject();
    void destroyGameObject(GameObject* obj);
    void destroyGameObject(Core::UUID id);

private:
    std::unordered_map<Core::UUID, std::shared_ptr<GameObject>> m_entityMap;
};
}
