#pragma once

#include "Core/Layer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/buffers/IndexBuffer.h"
#include "Renderer/buffers/VertexArray.h"
#include "Renderer/buffers/VertexBuffer.h"

class SandboxLayer : public Core::Layer
{
  private:
    Renderer::Renderer renderer;

    Renderer::VertexArray m_va;
    Renderer::VertexBuffer m_vb;
    Renderer::IndexBuffer m_ib;
    Renderer::Shader m_shader;
    Renderer::Texture m_texture;

  public:
    SandboxLayer();
    virtual ~SandboxLayer();

    virtual void onUpdate() override;
    virtual void onRender() override;

    virtual void onEvent(Core::Event &event) override;

    virtual void onDetach() override;
};
