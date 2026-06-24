#include "MeshRenderer.h"

#include "Engine/Core/Reflection/ClassDescriptor.h"
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

void MeshRenderer::registerReflection(Core::ClassDescriptor& desc)
{
    desc.addProperty("mesh", &MeshRenderer::mesh);
    desc.addProperty("material", &MeshRenderer::material);
}

}
