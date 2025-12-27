#include <memory>
#pragma onceSandb

#include "Engine/Core/Layer.h"
#include "Engine/Objects/Camera.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"

class SandboxLayer : public Core::Layer
{
private:
    std::unique_ptr<Engine::Camera> camera;

    std::unique_ptr<Renderer::Mesh> cubeMesh;
    std::unique_ptr<Renderer::Mesh> cubeLineMesh;

    Renderer::Renderer renderer;
    std::unique_ptr<Renderer::Shader> whiteShader;
    std::unique_ptr<Renderer::Shader> basicShader;

    float m_rotation = 0.0f;

public:
    SandboxLayer();
    virtual ~SandboxLayer();

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event& event) override;

    virtual void onDetach() override;
};
