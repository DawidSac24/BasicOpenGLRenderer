#include "Renderer.h"
#include "Engine/Renderer/Material.h"

namespace Renderer
{

std::shared_ptr<Shader> Renderer::s_currentShader = nullptr;

std::unique_ptr<Renderer::SceneData> Renderer::s_sceneData = std::make_unique<Renderer::SceneData>();

void Renderer::init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 2. Fix Depth Testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS); // <--- CHANGED: Draw things that are CLOSER (the default)

    // 3. Fix Culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Hide the back faces
    glFrontFace(GL_CCW);
}

void Renderer::shutdown()
{
    // Cleanup if needed
}

void Renderer::beginScene(const glm::mat4& projection, const glm::mat4& view)
{
    s_sceneData->viewProjectionMatrix = projection * view;
    s_currentShader = nullptr;
}

void Renderer::endScene() { }

void Renderer::submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material,
    const glm::mat4& transform, GLenum drawMode)
{
    // 1. Bind Material (Texture + Shader)
    material->bind();
    auto shader = material->getShader();

    // 2. Optimization: Only upload ViewProjection if the shader actually changed
    if (shader != s_currentShader)
    {
        shader->setUniformMat4f("u_viewProjection", s_sceneData->viewProjectionMatrix);
        s_currentShader = shader;
    }

    // 3. Upload Model Matrix (Always changes per object)
    shader->setUniformMat4f("u_model", transform);

    // 4. Draw
    mesh->bind();
    glDrawElements(drawMode, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);
}

}
