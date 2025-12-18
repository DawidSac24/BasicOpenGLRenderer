#include "SandboxLayer.h"

#include "Core/Application.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"

static float s_positions[] = {
    -50.0f, -50.0f, 0.0f, 0.0f, 50.0f,  -50.0f, 1.0f, 0.0f,
    50.0f,  50.0f,  1.0f, 1.0f, -50.0f, 50.0f,  0.0f, 1.0f,
};

static unsigned int s_indices[] = {0, 1, 2, 2, 3, 0};

SandboxLayer::SandboxLayer()
    : m_va(),
      m_vb(s_positions, 4 * 4 * sizeof(float)),
      m_ib(s_indices, 6),
      m_shader("../res/shaders/basic.vert", "../res/shaders/basic.frag"),
      m_texture("../res/textures/texture.png") {
  // The Constructor Body is now only for configuring state,
  // because the objects are already created!

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
  glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

  glm::mat4 mvp = proj * view * model;

  m_shader.bind();
  m_shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
  m_shader.setUniformMat4f("u_mvp", mvp);

  m_texture.bind();
  m_shader.setUniform1i("u_texture", 0);

  // Unbind (using dot operator, not arrow)
  m_va.unbind();
  m_vb.unbind();
  m_ib.unbind();
  m_shader.unbind();
}
SandboxLayer::~SandboxLayer() {}

void SandboxLayer::onUpdate() {
  // Our state
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to create a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!"
                                    // and append into it.

    ImGui::Text("This is some useful text.");  // Display some text (you can use
                                               // a format strings too)
    ImGui::Checkbox(
        "Demo Window",
        &show_demo_window);  // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f,
                       1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3(
        "clear color",
        (float*)&clear_color);  // Edit 3 floats representing a color

    if (ImGui::Button("Button"))  // Buttons return true when clicked (most
                                  // widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window);  // Pass a pointer to our bool variable (the
                                // window will have a closing button that will
                                // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me")) show_another_window = false;
    ImGui::End();
  }

  // Rendering
  ImGui::Render();
  int display_w, display_h;
  GLFWwindow* window = Core::Application::get().getWindow()->getHandle();

  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
               clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void SandboxLayer::onRender() {
  renderer.clear();

  m_texture.bind();
  m_shader.bind();

  // Pass objects by reference to draw command
  // (Assuming your Renderer::draw takes (VertexArray&, IndexBuffer&, Shader&))
  renderer.draw(m_va, m_ib, m_shader);
}

void SandboxLayer::onEvent(Core::Event& event) {}

void SandboxLayer::onDetach() {}
