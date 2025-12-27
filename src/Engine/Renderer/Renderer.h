#pragma once

#include "Camera.h"
#include "Engine/Renderer/Material.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <memory>

namespace Renderer
{

class Renderer
{
public:
    static void init();
    static void shutdown();

    static void beginScene(Camera& camera);
    static void endScene();

    static void submit(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material,
        const glm::mat4& transform, GLenum drawMode = GL_TRIANGLES);

private:
    struct SceneData
    {
        glm::mat4 viewProjectionMatrix;
    };

    static std::unique_ptr<SceneData> s_sceneData;
};

class RenderCommand
{
public:
    static void clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
    static void setClearColor(const glm::vec4& color) { glClearColor(color.r, color.g, color.b, color.a); }

    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    static void enableBlending()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    static void disableDepthMask() { glDepthMask(GL_FALSE); }
    static void enableDepthMask() { glDepthMask(GL_TRUE); }
};
}
