#include "EntityFactory.h"

#include "Components/CameraComponent.h"
#include "Engine/Core/AssetManager.h"
#include "Engine/Renderer/MeshFactory.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Entity.h"

#include <iostream>
#include <memory>
#include <string>

namespace Engine
{
std::unique_ptr<Entity> EntityFactory::create(const std::string& name, EntityType type)
{
    if (type == EntityType::Empty)
    {
        return std::make_unique<Entity>(name, m_scene);
    }

    switch (type)
    {
    case EntityType::Unknown:
        std::cerr << "Entity creation error: invalid Entity Type" << std::endl;
        return nullptr;

    case EntityType::Empty:
        return std::make_unique<Entity>(name, m_scene);

    case EntityType::Camera:
        return createCamera(name);

    case EntityType::Count:
        return nullptr;

    default:
        return createPrimitiveEntity(name, type);
    }
}

std::unique_ptr<Entity> EntityFactory::createPrimitiveEntity(const std::string& name, EntityType type)
{
    auto newEntity = std::make_unique<Entity>(name, m_scene);

    std::string entityName = EntityTypeToString(type);
    auto mesh = Core::AssetManager::getMesh(entityName);

    if (!mesh)
    {
        std::cerr << "CRITICAL: " << entityName << " mesh missing! Generating fallback." << std::endl;
        mesh = Renderer::MeshFactory::create(type); // Force create it
        Core::AssetManager::addMesh(entityName, mesh);
    }

    auto material = Renderer::MeshFactory::getDefaultMaterial();

    newEntity->addComponent<MeshRenderer>(newEntity.get(), mesh, material);

    return newEntity;
}

std::unique_ptr<Entity> EntityFactory::createCamera(const std::string& name)
{
    auto entity = std::make_unique<Entity>(name, m_scene);

    entity->transform->setPosition({ 0.0f, 0.0f, 5.0f });

    entity->addComponent<CameraComponent>(entity.get());

    return entity;
}
}
