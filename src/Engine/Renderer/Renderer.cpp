#include "Renderer.h"

namespace Renderer
{

// Define the static member
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

void Renderer::beginScene(Camera& camera)
{
    // Calculate VP Matrix once per frame
    s_sceneData->viewProjectionMatrix = camera.getViewProjection();
}

void Renderer::endScene()
{
    // Nothing to do yet
}

void Renderer::submit(const std::unique_ptr<Mesh>& mesh, const std::unique_ptr<Shader>& shader,
    const glm::mat4& transform, GLenum drawMode)
{
    // 1. Bind Shader
    shader->bind();

    // 2. Upload Camera Uniform (Calculated in beginScene)
    // Make sure your shaders use the name "u_ViewProjection"
    shader->setUniformMat4f("u_viewProjection", s_sceneData->viewProjectionMatrix);

    // 3. Upload Object Transform
    shader->setUniformMat4f("u_model", transform);

    // 4. Draw
    // Note: mesh->bind() needs to be public in your Mesh class!
    mesh->bind();

    // We need access to index count.
    // Ensure Mesh has: GetIndexCount() or similar.
    // Assuming mesh->draw() is removed, we do raw GL calls here:
    glDrawElements(drawMode, mesh->getIndexCount(), GL_UNSIGNED_INT, nullptr);

    // OR if you kept Mesh::draw, call it here (but passing 0 uniforms):
    // mesh->draw(..., drawMode);
}

}
