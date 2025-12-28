#include "Renderer.h"
#include "Engine/Renderer/Material.h"

namespace Renderer
{

std::unique_ptr<Renderer::SceneData> Renderer::s_sceneData = std::make_unique<Renderer::SceneData>();

void Renderer::init()
{
    RenderCommand::enableBlending();
    glEnable(GL_DEPTH_TEST);
}

void Renderer::shutdown()
{
    // Cleanup if needed
}

void Renderer::beginScene(const glm::mat4& projection, const glm::mat4& view)
{
    s_sceneData->viewProjectionMatrix = projection * view;
}

void Renderer::endScene() { }

void Renderer::submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material,
    const glm::mat4& transform, GLenum drawMode)
{
    material->bind();

    std::shared_ptr<Shader> shader = material->getShader();

    shader->setUniformMat4f("u_viewProjection", s_sceneData->viewProjectionMatrix);

    shader->setUniformMat4f("u_model", transform);

    mesh->bind();
    glDrawElements(drawMode, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
}

}
