#include "AssetManager.h"

#include "Engine/Core/FyleSystem.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/MeshFactory.h"

namespace Engine
{

// Initialize static members
std::unordered_map<std::string, std::shared_ptr<Renderer::Shader>> AssetManager::s_shaders;
std::unordered_map<std::string, std::shared_ptr<Renderer::Texture>> AssetManager::s_textures;
std::unordered_map<std::string, std::shared_ptr<Renderer::Mesh>> AssetManager::s_meshes;
std::unordered_map<std::string, std::shared_ptr<Renderer::Material>> AssetManager::s_materials;

// --- SHADERS ---
std::shared_ptr<Renderer::Shader> AssetManager::loadShader(
    const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
    // 1. Create the shader
    auto shader = std::make_shared<Renderer::Shader>(vertPath, fragPath);

    // 2. Store it
    s_shaders[name] = shader;

    return shader;
}

std::shared_ptr<Renderer::Shader> AssetManager::getShader(const std::string& name)
{
    // Check if key exists
    if (s_shaders.find(name) == s_shaders.end())
    {
        std::cerr << "[AssetManager] Shader not found: " << name << std::endl;
        return nullptr; // Or return a default "Error Pink" shader
    }
    return s_shaders[name];
}

// --- TEXTURES ---
std::shared_ptr<Renderer::Texture> AssetManager::loadTexture(
    const std::string& name, const std::string& filepath, const std::string& type)
{
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

// --- MESHES ---
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

// --- MATERIALS ---
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
    // 1. Load Defaults
    // Create a default shader so we never crash
    auto basicShader
        = loadShader("BasicShader", "res/shaders/basic.vert", "res/shaders/basic.frag");

    // 2. Load Models
    Renderer::MeshFactory::CreateCube(); // Ensure this adds to the map!
    Renderer::MeshFactory::CreateSphere(32);

    // 3. Load Default Texture
    loadTexture("White", "res/textures/texture.png"); // Create a 1x1 white png or generate it
}

void AssetManager::clear()
{
    s_shaders.clear();
    s_textures.clear();
    s_meshes.clear();
    s_materials.clear();
}

}