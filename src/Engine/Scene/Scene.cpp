#include "Scene.h"

#include "Engine/Math/Transform.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h"
#include "Engine/Scene/EntityFactory.h"
#include "Entity.h"

#include <algorithm>
#include <iostream>
#include <memory>

namespace Engine
{

Scene::Scene(const std::string& name)
    : name(name)
{
}

void Scene::onRender()
{
    CameraComponent* mainCam = nullptr;
    TransformComponent* camTransform = nullptr;

    // Iterate through all entities that have a CameraComponent
    // (Assuming you have a registry or list of entities)
    for (auto& [uuid, entity] : m_entityMap)
    {
        if (auto* cam = entity->getComponent<CameraComponent>())
        {
            if (cam->primary)
            {
                mainCam = cam;
                camTransform = entity->transform; // Get the standard transform
                break;
            }
        }
    }

    // 2. If we found a camera, Begin the Scene
    if (mainCam && camTransform)
    {
        // Calculate matrices
        glm::mat4 projection = mainCam->getProjection();

        // View Matrix is Inverse of World Matrix (Camera moves right = World moves left)
        glm::mat4 view = glm::inverse(camTransform->getWorldMatrix());

        // Pass distinct matrices to Renderer (or multiply them here if Renderer expects VP)
        Renderer::Renderer::beginScene(projection, view);

        // 3. Draw all MeshRenderers
        for (auto& [uuid, entity] : m_entityMap)
        {
            if (auto* meshRenderer = entity->getComponent<MeshRenderer>())
            {
                meshRenderer->onRender(); // Calls Renderer::submit inside
            }
        }

        Renderer::Renderer::endScene();
    }
}

Entity* Scene::getEntityByUUID(Core::UUID uuid)
{
    auto it = m_entityMap.find(uuid);
    if (it != m_entityMap.end())
        return it->second.get();

    return nullptr;
}

Entity* Scene::createEntity(const std::string& p_name, EntityType type)
{
    auto newEntity = EntityFactory::create(p_name, type);

    Core::UUID id = newEntity->getID();
    Entity* rawPointer = newEntity.get();

    m_entityMap[id] = std::move(newEntity);

    return rawPointer;
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
