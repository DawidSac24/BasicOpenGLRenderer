#include <memory>
#pragma onceSandb

#include "Core/Application.h"
#include "Core/Layer.h"
#include "Engine/Camera.h"
#include "Engine/Mesh.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

class SandboxLayer : public Core::Layer
{
private:
    std::unique_ptr<Engine::Camera> camera;
    std::unique_ptr<Engine::Mesh> cubeMesh;

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
