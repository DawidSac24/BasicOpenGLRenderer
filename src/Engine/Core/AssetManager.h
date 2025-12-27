#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Texture.h"

namespace Engine
{

class AssetManager
{
public:
    static std::shared_ptr<Renderer::Shader> loadShader(
        const std::string& name, const std::string& vertPath, const std::string& fragPath);
    static std::shared_ptr<Renderer::Shader> getShader(const std::string& name);

    static std::shared_ptr<Renderer::Texture> loadTexture(
        const std::string& name, const std::string& filepath, const std::string& type = "diffuse");
    static std::shared_ptr<Renderer::Texture> getTexture(const std::string& name);

    static std::shared_ptr<Renderer::Mesh> getMesh(const std::string& name);
    static void addMesh(const std::string& name, std::shared_ptr<Renderer::Mesh> mesh);

    static void loadModels();

    static void clear();

private:
    AssetManager() = default;

    static std::unordered_map<std::string, std::shared_ptr<Renderer::Shader>> s_Shaders;
    static std::unordered_map<std::string, std::shared_ptr<Renderer::Texture>> s_Textures;
    static std::unordered_map<std::string, std::shared_ptr<Renderer::Mesh>> s_Meshes;
};

}
