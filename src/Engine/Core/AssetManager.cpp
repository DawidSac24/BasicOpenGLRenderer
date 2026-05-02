#include "AssetManager.h"

#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/MeshFactory.h"
#include "Engine/Scene/Entity.h"
#include <iostream>

namespace Core
{

std::unordered_map<std::string, std::shared_ptr<Renderer::Shader>> AssetManager::s_shaders;
std::unordered_map<std::string, std::shared_ptr<Renderer::Texture>> AssetManager::s_textures;
std::unordered_map<std::string, std::shared_ptr<Renderer::Mesh>> AssetManager::s_meshes;
std::unordered_map<std::string, std::shared_ptr<Renderer::Material>> AssetManager::s_materials;

std::shared_ptr<Renderer::Shader> AssetManager::loadShader(
    const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
    if (s_shaders.find(name) != s_shaders.end())
    {
        return s_shaders[name];
    }

    auto shader = std::make_shared<Renderer::Shader>(vertPath, fragPath);
    s_shaders[name] = shader;
    return shader;
}

std::shared_ptr<Renderer::Shader> AssetManager::getShader(const std::string& name)
{
    if (s_shaders.find(name) == s_shaders.end())
    {
        std::cerr << "[AssetManager] Shader not found: " << name << std::endl;
        return nullptr;
    }
    return s_shaders[name];
}

std::shared_ptr<Renderer::Texture> AssetManager::loadTexture(
    const std::string& name, const std::string& filepath, const std::string& type)
{
    if (s_textures.find(name) != s_textures.end())
    {
        return s_textures[name];
    }

    auto texture = std::make_shared<Renderer::Texture>(filepath, type.c_str());
    s_textures[name] = texture;
    return texture;
}

std::shared_ptr<Renderer::Texture> AssetManager::getTexture(const std::string& name)
{
    if (s_textures.find(name) == s_textures.end())
    {
        std::cerr << "[AssetManager] Texture not found: " << name << std::endl;
        // Return a default white texture if missing?
        return nullptr;
    }
    return s_textures[name];
}

void AssetManager::addMesh(const std::string& name, std::shared_ptr<Renderer::Mesh> mesh)
{
    s_meshes[name] = mesh;
}
std::shared_ptr<Renderer::Mesh> AssetManager::getMesh(const std::string& name)
{
    if (s_meshes.find(name) == s_meshes.end())
    {
        std::cerr << "[AssetManager] Mesh not found: " << name << std::endl;
        return nullptr;
    }
    return s_meshes[name];
}

void AssetManager::addMaterial(const std::string& name, std::shared_ptr<Renderer::Material> material)
{
    s_materials[name] = material;
}
std::shared_ptr<Renderer::Material> AssetManager::getMaterial(const std::string& name)
{
    if (s_materials.find(name) == s_materials.end())
    {
        std::cerr << "[AssetManager] Material not found: " << name << std::endl;
        return nullptr;
    }
    return s_materials[name];
}

void AssetManager::loadAssets()
{
    loadShader("defaultShader", "res/default/Shaders/default.vert", "res/default/Shaders/default.frag");
    loadTexture("defaultTexture", "res/default/Textures/greyTexture.jpg");

    std::shared_ptr<Renderer::Material> defaultMaterial = Renderer::MeshFactory::getDefaultMaterial();
    addMaterial(defaultMaterial->getName(), defaultMaterial);

    addMesh(Engine::EntityTypeToString(Engine::EntityType::Cube), Renderer::MeshFactory::create(Engine::EntityType::Cube));
    addMesh(Engine::EntityTypeToString(Engine::EntityType::Sphere), Renderer::MeshFactory::create(Engine::EntityType::Sphere));
    addMesh(Engine::EntityTypeToString(Engine::EntityType::Plane), Renderer::MeshFactory::create(Engine::EntityType::Plane));

    std::cout << "[AssetManager] Default assets initialized." << std::endl;
}

void AssetManager::clear()
{
    s_shaders.clear();
    s_textures.clear();
    s_meshes.clear();
    s_materials.clear();
}

}
