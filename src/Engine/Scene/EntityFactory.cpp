#include "EntityFactory.h"

#include "Components/CameraComponent.h"
#include "Engine/Core/AssetManager.h"
#include "Engine/Renderer/MeshFactory.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Entity.h"

#include <memory>

namespace Engine
{
std::unique_ptr<Entity> EntityFactory::create(const std::string& name, EntityType type)
{
    switch (type)
    {
    case EntityType::Empty:
        return createEmpty(name);
    case EntityType::Cube:
        return createCube(name);
    case EntityType::Sphere:
        return createSphere(name);
    case EntityType::Plane:
        return createPlane(name);
    case EntityType::Camera:
        return createCamera(name);
    }

    std::cerr << "Entity creation error: invalid Entity Type" << std::endl;
    return nullptr;
}

std::unique_ptr<Entity> EntityFactory::createEmpty(const std::string& name)
{
    return std::make_unique<Entity>(name);
}

std::unique_ptr<Entity> EntityFactory::createCube(const std::string& name)
{
    auto newEntity = std::make_unique<Entity>(name);

    // --- 1. Get Mesh (Safely) ---
    auto mesh = AssetManager::getMesh("Cube");
    if (!mesh)
    {
        std::cerr << "CRITICAL: 'Cube' mesh missing! Generating fallback." << std::endl;
        mesh = Renderer::MeshFactory::CreateCube(); // Force create it
        AssetManager::addMesh("Cube", mesh);
    }

    // --- 2. Get Shader (Safely) ---
    auto shader = AssetManager::getShader("BasicShader");
    if (!shader)
    {
        std::cerr << "CRITICAL: 'BasicShader' missing!" << std::endl;
        // You might want to return here or load a hardcoded fallback shader
    }

    // --- 3. Create Material ---
    auto material = std::make_shared<Renderer::Material>(shader);
    material->setFloat4("u_Color", { 1.0f, 1.0f, 1.0f, 1.0f });

    // --- 4. Add Component ---
    // If mesh or material are nullptr here, the Inspector will show them as empty.
    newEntity->addComponent<MeshRenderer>(newEntity.get(), mesh, material);

    return newEntity;
}

std::unique_ptr<Entity> EntityFactory::createSphere(const std::string& name)
{
    return nullptr;
}

std::unique_ptr<Entity> EntityFactory::createPlane(const std::string& name)
{
    return nullptr;
}

std::unique_ptr<Entity> EntityFactory::createCamera(const std::string& name)
{
    auto entity = std::make_unique<Entity>(name);

    entity->transform->setPosition({ 0.0f, 0.0f, 5.0f });

    auto* camComp = entity->addComponent<CameraComponent>(entity.get());
    camComp->primary = true; // Make it active

    return entity;
}
}
