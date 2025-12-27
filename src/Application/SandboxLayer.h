#pragma once

#include "Engine/Core/Layer.h"
#include "Engine/Events/WindowEvents.h"
#include "Engine/Renderer/Camera.h"
#include "Engine/Renderer/Mesh.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Renderer/Shader.h"

#include <memory>

class SandboxLayer : public Core::Layer
{
private:
    std::unique_ptr<Renderer::Camera> camera;

    std::unique_ptr<Renderer::Mesh> cubeMesh;
    std::unique_ptr<Renderer::Mesh> cubeLineMesh;

    std::unique_ptr<Renderer::Shader> whiteShader;
    std::unique_ptr<Renderer::Shader> basicShader;

    float m_rotation = 0.0f;

public:
    SandboxLayer();
    virtual ~SandboxLayer();

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event& event) override;
    bool onWindowResize(Core::WindowResizeEvent& e);

    virtual void onDetach() override;
};
