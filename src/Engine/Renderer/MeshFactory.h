#pragma once

#include "Engine/Renderer/Mesh.h"

#include <memory>

namespace Renderer
{
class MeshFactory
{
public:
    static std::shared_ptr<Renderer::Mesh> CreateCube();
    static std::shared_ptr<Renderer::Mesh> CreateSphere(int segments);
    static std::shared_ptr<Renderer::Mesh> CreatePlane();
};
}
