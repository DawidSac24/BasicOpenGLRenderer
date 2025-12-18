#include "MVPTestLayer.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"

static float s_positions[] = {
    -50.0f, -50.0f, 0.0f, 0.0f, 50.0f,  -50.0f, 1.0f, 0.0f,
    50.0f,  50.0f,  1.0f, 1.0f, -50.0f, 50.0f,  0.0f, 1.0f,
};

static unsigned int s_indices[] = {0, 1, 2, 2, 3, 0};

MVPTestLayer::MVPTestLayer()
    : m_va(),
      m_vb(s_positions, 4 * 4 * sizeof(float)),
      m_ib(s_indices, 6),
      m_shader("../res/shaders/basic.vert", "../res/shaders/basic.frag"),
      m_texture("../res/textures/texture.png") {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setup the Layout
  Renderer::VertexBufferLayout layout;
  layout.push<float>(2);
  layout.push<float>(2);

  // Link the VB to the VA
  // Note: m_vb and m_va are objects now, so we pass them directly (or by
  // reference)
  m_va.addBuffer(m_vb, layout);

  // Shader Uniforms
  proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
  view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  m_translation = glm::vec3(0, 0, 0);
}

MVPTestLayer::~MVPTestLayer() {}

void MVPTestLayer::onUpdate() {}

void MVPTestLayer::onRender() {
  renderer.clear();

  ImGui::Begin("MVP settings");
  ImGui::SliderFloat3("Translation", &m_translation.x, 0.0f, 960.0f);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / imGuiIO.Framerate, imGuiIO.Framerate);
  ImGui::End();

  ImGui::Render();

  m_texture.bind();
  m_shader.bind();

  model = glm::translate(glm::mat4(1.0f), m_translation);
  mvp = proj * view * model;

  m_shader.setUniformMat4f("u_mvp", mvp);

  // Pass objects by reference to draw command
  // (Assuming your Renderer::draw takes (VertexArray&, IndexBuffer&, Shader&))
  renderer.draw(m_va, m_ib, m_shader);
}

void MVPTestLayer::onEvent(Core::Event& event) {}

void MVPTestLayer::onDetach() {}
