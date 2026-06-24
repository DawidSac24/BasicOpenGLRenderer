#include "Scene.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/Components/CameraComponent.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Components/TransformComponent.h"
#include "Engine/Scene/EntityFactory.h"
#include "Entity.h"

#include <cstdint>
#include <fmt/chrono.h>
#include <memory>

namespace Engine
{

Scene::Scene(const std::string& name)
    : name(name)
    , m_entityFactory(this)
{
}

void Scene::init()
{
    m_primaryCamera = createEntity("Main Camera", EntityType::Camera);
    m_primaryCamera->getComponent<CameraComponent>()->setIsPrimary(true);
}

void Scene::onRender()
{
    if (m_entityList.empty())
        return;

    CameraComponent* mainCam = m_primaryCamera->getComponent<CameraComponent>();
    TransformComponent* camTransform = m_primaryCamera->transform;

    if (mainCam && camTransform)
    {
        glm::mat4 projection = mainCam->getProjection();
        glm::mat4 view = glm::inverse(camTransform->getWorldMatrix());

        Renderer::Renderer::beginScene(projection, view);

        for (auto entity : m_entityList)
        {
            auto* meshRenderer = entity->getComponent<MeshRenderer>();

            if (meshRenderer && meshRenderer->mesh && meshRenderer->material)
            {
                glm::mat4 worldMatrix = entity->transform->getWorldMatrix();

                Renderer::Renderer::submit(meshRenderer->mesh, meshRenderer->material, worldMatrix);
            }
        }

        Renderer::Renderer::endScene();
    }
}

Entity* Scene::getEntityByUUID(Core::UUID uuid) const
{
    auto it = m_entityMap.find(uuid);
    if (it != m_entityMap.end())
        return it->second.get();

    return nullptr;
}

bool Scene::addEntity(std::shared_ptr<Entity> entity)
{
    if (!m_entityMap.insert({ entity->getID(), entity }).second)
        return false;

    m_entityList.push_back(entity.get());
    CameraComponent* camera = entity->getComponent<CameraComponent>();
    if (camera)
        camera->setIsPrimary(false);

    return true;
}

Entity* Scene::createEntity(const std::string& p_name, EntityType type)
{
    std::unique_ptr<Entity> newEntity = m_entityFactory.create(p_name, type);
    if (newEntity == nullptr)
        return nullptr;

    Core::UUID id = newEntity->getID();
    Entity* rawPointer = newEntity.get();

    m_entityList.push_back(rawPointer);

    rawPointer->orderIterator = std::prev(m_entityList.end());

    m_entityMap[id]
        = std::move(newEntity);

    return rawPointer;
}

void Scene::destroyEntity(Entity* obj)
{
    if (!obj)
        return;

    m_entityList.erase(obj->orderIterator);
    m_entityMap.erase(obj->getID());
}

void Scene::setPrimaryCamera(Entity* targetEntity)
{
    m_primaryCamera->getComponent<CameraComponent>()->setIsPrimary(false);

    m_primaryCamera = targetEntity;
    targetEntity->getComponent<CameraComponent>()->setIsPrimary(true);
}

void Scene::updateCamerasViewport(uint32_t width, uint32_t height)
{
    for (auto& [uuid, entity] : m_entityMap)
    {
        if (auto* cam = entity->getComponent<CameraComponent>())
        {
            if (cam->isPrimary())
            {
                cam->setViewportSize(width, height);
                break;
            }
        }
    }
}
}
