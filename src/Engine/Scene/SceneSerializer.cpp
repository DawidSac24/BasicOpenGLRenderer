#include "SceneSerializer.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/MeshFactory.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/Component.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h"
#include "Engine/Scene/Entity.h"

#include <fstream>
#include <glm/fwd.hpp>
#include <iostream>
#include <memory>

#define SERIALIZE_COMPONENT(T, entity, outJson)      \
    if (entity->hasComponent<T>())                   \
    {                                                \
        json& componentNode = outJson[#T];           \
        auto* component = entity->getComponent<T>(); \
        serialize##T(*component, componentNode);     \
    }
#define DESERIALIZE_COMPONENT(T, entity, data) \
    if (data.contains(#T))                     \
    {                                          \
        json& componentNode = data[#T];        \
        deserialize##T(entity, componentNode); \
    }

namespace Engine
{
SceneSerializer::SceneSerializer(Scene* scene)
    : m_scene(scene)
{
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

        if (entity->hasComponents())
            entityJson["components"] = serializeComponents(entity);

        entities.push_back(entityJson);
    }
    return entities;
}

json SceneSerializer::serializeComponents(Entity* entity) const
{
    json components = json::array();

    SERIALIZE_COMPONENT(TransformComponent, entity, components)
    SERIALIZE_COMPONENT(CameraComponent, entity, components)
    // SERIALIZE_COMPONENT(MeshRenderer, entity, components)
    // SERIALIZE_COMPONENT(ScriptComponent, entity, components)

    return components;
}

void SceneSerializer::deserializeEntities(json& data)
{
    if (!data.contains("entities"))
        return;

    for (auto& entityData : data["entities"])
    {
        uint64_t uuid = data["ID"];
        std::string name = data["name"];

        std::shared_ptr<Entity> entity = std::make_shared<Entity>(Core::UUID(uuid), name, m_scene);
        m_scene->addEntity(entity);

        if (data.contains("components"))
            deserializeComponents(entity.get(), entityData["components"]);
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
    }

    return;
}

void SceneSerializer::deserializeComponents(Entity* entity, json& components)
{
    DESERIALIZE_COMPONENT(TransformComponent, entity, components)
    SERIALIZE_COMPONENT(CameraComponent, entity, components)
    // SERIALIZE_COMPONENT(MeshRenderer, entity, components)
    // SERIALIZE_COMPONENT(ScriptComponent, entity, components)
}

void SceneSerializer::serializeTransformComponent(TransformComponent& c, json& out)
{
    glm::vec3 pos = c.getPosition();
    glm::quat rot = c.getRotation();
    glm::vec3 scale = c.getScale();

    out["position"] = { pos.x, pos.y, pos.z };
    out["rotation"] = { rot.x, rot.y, rot.z, rot.w };
    out["scale"] = { scale.x, scale.y, scale.z };
}
void SceneSerializer::deserializeTransformComponent(Entity* entity, json& data)
{
    auto transform = entity->getComponent<TransformComponent>();
    json pos = data["position"];
    transform->setPosition({ pos[0], pos[1], pos[2] });
    json rot = data["rotation"];
    transform->setRotation({ rot[0], rot[1], rot[2], rot[3] });
    json scale = data["scale"];
    transform->setScale({ scale[0], scale[1], scale[2] });
}

void SceneSerializer::serializeCameraComponent(CameraComponent& c, json& out)
{
    out["isPrimary"] = c.isPrimary();
}
void SceneSerializer::deserializeCameraComponent(Entity* entity, json& data)
{
    auto camera = entity->addComponent<CameraComponent>(entity);
    if (data["isPrimary"])
        camera->setIsPrimary(true);
}

void SceneSerializer::serializeMeshRenderer(MeshRenderer& c, json& out)
{
    json& mesh = out["mesh"];
    mesh["name"] = c.mesh->getName();

    json& material = out["material"];
    material["name"] = c.material->getName();

    mesh["filepath"] = c.mesh->getFilepath();
    material["filepath"] = c.material->getFilepath();
}

void SceneSerializer::deserializeMeshRenderer(Entity* entity, json& data)
{
    std::shared_ptr<Renderer::Mesh> mesh;
    std::shared_ptr<Renderer::Material> material;

    int typeInt = data.value("primitiveType", (int)EntityType::Unknown);
    EntityType type = static_cast<EntityType>(typeInt);

    if (type != EntityType::Unknown && type != EntityType::Empty)
    {
        mesh = Renderer::MeshFactory::create(type);
    }
    else if (data.contains("filePath"))
    {
        std::string path = data["filePath"];
        // Use your AssetManager to load/retrieve it
        // mesh = Core::AssetManager::getMesh(path);
    }

    // 2. Handle Material (Simplified for now)
    // You might want to save a "materialPath" in JSON later.
    material = Renderer::MeshFactory::getDefaultMaterial();

    // 3. Add Component
    // Safety check: ensure mesh exists before adding component
    if (mesh)
    {
        // NOTE: You don't need to pass 'entity' as the first arg if addComponent handles it implicitly.
        // If your Component constructor needs the Entity*, then keep it.
        entity->addComponent<MeshRenderer>(entity, mesh, material);
    }
}

};
