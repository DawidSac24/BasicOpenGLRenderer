#pragma once

#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Scene/Entity.h"

#include <memory>

namespace Renderer
{
class MeshFactory
{
public:
    static std::shared_ptr<Mesh> create(Engine::EntityType type, int segments = 32);
    static std::shared_ptr<Material> getDefaultMaterial();
    std::vector<std::string> getPrimitiveTypeNames();

private:
    static std::shared_ptr<Mesh> createCube();
    static std::shared_ptr<Mesh> createSphere(int segments);
    static std::shared_ptr<Mesh> createPlane();
};
}
