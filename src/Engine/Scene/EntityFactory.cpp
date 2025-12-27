#include "EntityFactory.h"
#include "Engine/Core/AssetManager.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Scene/Components/MeshRenderer.h"
#include "Engine/Scene/Entity.h"
#include "MeshFactory.h"
#include <memory>

namespace Engine
{
EntityFactory::EntityFactory() { }

Entity* EntityFactory::createEntity(EntityType type, std::string* name)
{
    switch (type)
    {
    case EntityType::Empty:
        return createEmptyEntity(name);
    case EntityType::Square:
        return createCubeEntity(name);
    case EntityType::Sphere:
        return createSphereEntity(name);
    case EntityType::Plane:
        return createPlaneEntity(name);
    case EntityType::Camera:
        return createCameraEntity(name);
    }
}

Entity* EntityFactory::createEmptyEntity(std::string* name)
{
    return new Entity(name);
}

Entity* EntityFactory::createCubeEntity(std::string* name)
{
    Entity* newEntity = new Entity(name);

    std::shared_ptr<Renderer::Mesh> cubeMesh = AssetManager::getMesh("CubeMesh");

    if (cubeMesh == nullptr)
    {
        cubeMesh = MeshFactory::CreateCube();
        AssetManager::addMesh("CubeMesh", cubeMesh);
    }

    newEntity->addComponent<MeshRenderer>();

    return newEntity;
}

Entity* EntityFactory::createSphereEntity(std::string* name) { }

Entity* EntityFactory::createPlaneEntity(std::string* name) { }

Entity* EntityFactory::createCameraEntity(std::string* name)
{
    // Entity* newEntity = new Entity
}
}
