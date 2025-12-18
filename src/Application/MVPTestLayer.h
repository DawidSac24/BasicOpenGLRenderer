#pragma once

#include "Core/Layer.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/buffers/IndexBuffer.h"
#include "Renderer/buffers/VertexArray.h"
#include "Renderer/buffers/VertexBuffer.h"
#include "glm/fwd.hpp"
#include "imgui.h"

class MVPTestLayer : public Core::Layer {
 private:
  Renderer::Renderer renderer;

  Renderer::VertexArray m_va;
  Renderer::VertexBuffer m_vb;
  Renderer::IndexBuffer m_ib;
  Renderer::Shader m_shader;
  Renderer::Texture m_texture;

  glm::vec3 m_translation;
  glm::mat4 proj, view, model, mvp;

  ImGuiIO& imGuiIO = ImGui::GetIO();

 public:
  MVPTestLayer();
  virtual ~MVPTestLayer();

  virtual void onUpdate() override;
  virtual void onRender() override;

  virtual void onEvent(Core::Event& event) override;

  virtual void onDetach() override;
};
