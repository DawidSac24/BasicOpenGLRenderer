#pragma once

#include "Components/ScriptComponent.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h"
#include "Scene.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

namespace Engine
{
class SceneSerializer
{
public:
    SceneSerializer(Scene* scene);

    bool serialize(const std::string& filepath);
    bool deserialize(const std::string& filepath);

private:
    Scene* m_scene;

private:
    json serializeEntities(std::list<Entity*>* entityList) const;
    json serializeComponents(Entity* entity) const;

    void deserializeEntities(json& data);
    void deserializeComponents(Entity* entity, json& components);

private:
    static void serializeTransformComponent(TransformComponent& c, json& out);
    static void deserializeTransformComponent(Entity* entity, json& data);
    static void serializeCameraComponent(CameraComponent& c, json& out);
    static void deserializeCameraComponent(Entity* entity, json& data);
    static void serializeMeshRenderer(MeshRenderer& c, json& out);
    static void deserializeMeshRenderer(Entity* entity, json& data);
    static void serializeScriptComponent(ScriptComponent& c, json& out);
    static void deserializeScriptComponent(Entity* entity, json& data);
};
}
