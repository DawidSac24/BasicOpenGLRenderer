#pragma once

#include "Engine/Scene/Components/CameraComponent.h"
#include "Scene.h"

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
    json& serializeComponents(Entity* entity, json& data) const;

    void deserializeEntities(const json& data);
    void deserializeComponents(const json& data);

private:
    static void serializeTransform(TransformComponent& c, json& out);
    static void serializeCamera(CameraComponent& c, json& out);
    static void serializeMeshRenderer(TransformComponent& c, json& out);
    static void serializeScript(TransformComponent& c, json& out);
};
}
