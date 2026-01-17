#include "MeshRenderer.h"

#include "Engine/Scene/Components/Component.h"

namespace Engine
{
MeshRenderer::MeshRenderer(Entity* owner)
    : Component(owner)
{
}

MeshRenderer::MeshRenderer(Entity* owner, std::shared_ptr<Renderer::Mesh> m, std::shared_ptr<Renderer::Material> mat)
    : Component(owner)
    , mesh(m)
    , material(mat)
{
}

}
