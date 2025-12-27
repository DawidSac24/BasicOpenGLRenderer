#include "AssetManager.h"

#include "Engine/Scene/MeshFactory.h"

namespace Engine
{

// Initialize static members
std::unordered_map<std::string, std::shared_ptr<Renderer::Shader>> AssetManager::s_Shaders;
std::unordered_map<std::string, std::shared_ptr<Renderer::Texture>> AssetManager::s_Textures;
std::unordered_map<std::string, std::shared_ptr<Renderer::Mesh>> AssetManager::s_Meshes;

// --- SHADERS ---
std::shared_ptr<Renderer::Shader> AssetManager::loadShader(
    const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
    // 1. Create the shader
    auto shader = std::make_shared<Renderer::Shader>(vertPath, fragPath);

    // 2. Store it
    s_Shaders[name] = shader;

    return shader;
}

std::shared_ptr<Renderer::Shader> AssetManager::getShader(const std::string& name)
{
    // Check if key exists
    if (s_Shaders.find(name) == s_Shaders.end())
    {
        std::cerr << "[AssetManager] Shader not found: " << name << std::endl;
        return nullptr; // Or return a default "Error Pink" shader
    }
    return s_Shaders[name];
}

// --- TEXTURES ---
std::shared_ptr<Renderer::Texture> AssetManager::loadTexture(
    const std::string& name, const std::string& filepath, const std::string& type)
{
    auto texture = std::make_shared<Renderer::Texture>(filepath, type.c_str());
    s_Textures[name] = texture;
    return texture;
}

std::shared_ptr<Renderer::Texture> AssetManager::getTexture(const std::string& name)
{
    if (s_Textures.find(name) == s_Textures.end())
    {
        std::cerr << "[AssetManager] Texture not found: " << name << std::endl;
        // Return a default white texture if missing?
        return nullptr;
    }
    return s_Textures[name];
}

// --- MESHES ---
void AssetManager::addMesh(const std::string& name, std::shared_ptr<Renderer::Mesh> mesh)
{
    s_Meshes[name] = mesh;
}

std::shared_ptr<Renderer::Mesh> AssetManager::getMesh(const std::string& name)
{
    if (s_Meshes.find(name) == s_Meshes.end())
    {
        std::cerr << "[AssetManager] Mesh not found: " << name << std::endl;
        return nullptr;
    }
    return s_Meshes[name];
}

void AssetManager::loadModels()
{
    AssetManager::addMesh("Cube", MeshFactory::CreateCube());
    AssetManager::addMesh("Sphere", MeshFactory::CreateSphere(32));
}

void AssetManager::clear()
{
    s_Shaders.clear();
    s_Textures.clear();
    s_Meshes.clear();
}

}
