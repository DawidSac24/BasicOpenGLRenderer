#pragma once

#include "Engine/Math/Transform.h"
#include "Engine/Renderer/Material.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Scene/Components/Component.h"
#include "Engine/Scene/Entity.h"

#include <memory>

namespace Engine
{
class MeshRenderer : public Component
{
public:
    std::shared_ptr<Renderer::Mesh> mesh = nullptr;
    std::shared_ptr<Renderer::Material> material = nullptr;

public:
    MeshRenderer(Entity* owner);
    MeshRenderer(Entity* owner, std::shared_ptr<Renderer::Mesh> m, std::shared_ptr<Renderer::Material> mat);
    virtual ~MeshRenderer() = default;
};
}
