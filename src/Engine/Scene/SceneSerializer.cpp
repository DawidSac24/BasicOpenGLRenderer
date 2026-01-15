#include "SceneSerializer.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/TransformComponent.h"

#include <fstream>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>

#define SERIALIZE_COMPONENT(T, entity, outJson)      \
    if (entity->hasComponent<T>())                   \
    {                                                \
        json& componentNode = outJson[#T];           \
        auto& component = entity->getComponent<T>(); \
        serialize##T(component, componentNode);      \
    }

namespace Engine
{
SceneSerializer::SceneSerializer(Scene* scene)
    : m_scene(scene)
{
}

bool SceneSerializer::deserialize(const std::string& filepath)
{
    std::ifstream stream(filepath);
    if (!stream.is_open())
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return false;
    }
    json data;

    try
    {
        data = json::parse(stream);
    }
    catch (json::parse_error& ex)
    {
        std::cerr << "JSON Parse Error: " << ex.what() << std::endl;
        return false;
    }

    if (data.contains("name"))
        m_scene->setName(data["name"]);

    deserializeEntities(data);

    return true;
}

bool SceneSerializer::serialize(const std::string& filepath)
{
    std::ofstream newFile(filepath + m_scene->name + ".scene");
    if (!newFile.is_open())
    {
        std::cerr << "Failed to create file: " << filepath << std::endl;
        return false;
    }
    json data;
    data["name"] = m_scene->name;
    data["entities"] = serializeEntities(m_scene->getEntityList());

    newFile << data.dump(4);
    newFile.close();

    return true;
}

json SceneSerializer::serializeEntities(std::list<Entity*>* entityList) const
{
    json entities = json::array();

    for (const auto& entity : *entityList)
    {
        json entityJson;
        entityJson["ID"] = (uint64_t)entity->getID(); // Cast UUID to int for JSON
        entityJson["name"] = entity->name;

        if (entity->getParent())
        {
            entityJson["parentID"] = (uint64_t)entity->getParent()->getID();
        }
        else
        {
            entityJson["parentID"] = nullptr;
        }

        serializeComponents(entity, entityJson);

        entities.push_back(entityJson);
    }
    return entities;
}

void SceneSerializer::deserializeEntities(const json& data)
{
    if (!data.contains("entities"))
        return;

    for (auto& entityData : data["entities"])
    {
        uint64_t uuid = data["ID"];
        std::string name = data["name"];

        std::shared_ptr<Entity> entity = std::make_shared<Entity>(Core::UUID(uuid), name, m_scene);
        m_scene->addEntity(entity);
    }

    for (auto& entityData : data["entities"])
    {
        uint64_t childUUID = entityData["ID"];

        if (entityData.contains("parentID") && !entityData["parentID"].is_null())
        {
            uint64_t parentUUID = entityData["parentID"];

            auto child = m_scene->getEntityByUUID(Core::UUID(childUUID));
            auto parent = m_scene->getEntityByUUID(Core::UUID(parentUUID));

            if (child && parent)
            {
                child->setParent(parent);
            }
        }

        deserializeComponents(entityData);
    }

    return;
}

void SceneSerializer::deserializeComponents(const json& data)
{
    if (!data.contains("components"))
        return;
}

static void serializeTransform(TransformComponent& c, json& out)
{
    glm::vec3 pos = c.getPosition();
    glm::quat rot = c.getRotation();
    glm::vec3 scale = c.getScale();

    out["position"] = { pos.x, pos.y, pos.z };
    out["rotation"] = { rot.x, rot.y, rot.z, rot.w };
    out["scale"] = { scale.x, scale.y, scale.z };
}

static void serializeCamera(CameraComponent& c, json& out)
{
    out["isPrimary"] = c.isPrimary();
}

}
