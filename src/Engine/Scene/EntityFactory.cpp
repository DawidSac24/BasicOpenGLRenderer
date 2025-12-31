#include "EntityFactory.h"

#include "Components/CameraComponent.h"
#include "Engine/Core/AssetManager.h"
#include "Engine/Renderer/MeshFactory.h"
#include "Engine/Renderer/Texture.h"
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

    auto mesh = Core::AssetManager::getMesh("Cube");
    if (!mesh)
    {
        std::cerr << "CRITICAL: 'Cube' mesh missing! Generating fallback." << std::endl;
        mesh = Renderer::MeshFactory::CreateCube(); // Force create it
        Core::AssetManager::addMesh("Cube", mesh);
    }

    auto shader = Core::AssetManager::getShader("defaultShader");
    if (!shader)
    {
        std::cerr << "CRITICAL: 'BasicShader' missing!" << std::endl;
    }

    auto texture = Core::AssetManager::getTexture("defaultTexture");
    if (!texture)
    {
        std::cerr << "CRITICAL: 'GreyTexture' missing!" << std::endl;
    }

    // --- 3. Create Material ---
    auto material
        = std::make_shared<Renderer::Material>(shader);

    material->setTexture("u_Texture", texture);
    material->setFloat4("u_Color", { 1.0f, 1.0f, 1.0f, 1.0f });

    // --- 4. Add Component ---
    // If mesh or material are nullptr here, the Inspector will show them as empty.
    newEntity->addComponent<MeshRenderer>(newEntity.get(), mesh, material);

    return newEntity;
}

std::unique_ptr<Entity> EntityFactory::createSphere(const std::string& name)
{
    auto newEntity = std::make_unique<Entity>(name);

    auto mesh = Core::AssetManager::getMesh("Sphere");
    if (!mesh)
    {
        std::cerr << "CRITICAL: 'Sphere' mesh missing! Generating fallback." << std::endl;
        mesh = Renderer::MeshFactory::CreateCube(); // Force create it
        Core::AssetManager::addMesh("Sphere", mesh);
    }

    auto shader = Core::AssetManager::getShader("defaultShader");
    if (!shader)
    {
        std::cerr << "CRITICAL: 'defaultShader' missing!" << std::endl;
    }

    auto texture = Core::AssetManager::getTexture("defaultTexture");
    if (!texture)
    {
        std::cerr << "CRITICAL: 'defaultTexture' missing!" << std::endl;
    }

    // --- 3. Create Material ---
    auto material
        = std::make_shared<Renderer::Material>(shader);

    material->setTexture("u_Texture", texture);
    material->setFloat4("u_Color", { 1.0f, 1.0f, 1.0f, 1.0f });

    // --- 4. Add Component ---
    // If mesh or material are nullptr here, the Inspector will show them as empty.
    newEntity->addComponent<MeshRenderer>(newEntity.get(), mesh, material);

    return newEntity;
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
