#include "SandboxLayer.h"
#include "glm/ext/matrix_clip_space.hpp"

// Define data here so it's available for the Initializer List
static float s_positions[] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, 1.0f, 0.0f,
                              0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 1.0f};

static unsigned int s_indices[] = {0, 1, 2, 2, 3, 0};

SandboxLayer::SandboxLayer()
    : m_va(), m_vb(s_positions, 4 * 4 * sizeof(float)), m_ib(s_indices, 6),
      m_shader("../res/shaders/basic.vert", "../res/shaders/basic.frag"), m_texture("../res/textures/texture.png")
{
    // The Constructor Body is now only for configuring state,
    // because the objects are already created!

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Setup the Layout
    Renderer::VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    // Link the VB to the VA
    // Note: m_vb and m_va are objects now, so we pass them directly (or by reference)
    m_va.addBuffer(m_vb, layout);

    // Shader Uniforms
    glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.5f, 1.5f, -1.0f, 1.0f);

    m_shader.bind();
    m_shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
    m_shader.setUniformMat4f("u_mvp", proj);

    m_texture.bind();
    m_shader.setUniform1i("u_texture", 0);

    // Unbind (using dot operator, not arrow)
    m_va.unbind();
    m_vb.unbind();
    m_ib.unbind();
    m_shader.unbind();
}
SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::onUpdate()
{
}

void SandboxLayer::onRender()
{
    // m_renderer->clear(); // Ensure renderer is accessible

    m_texture.bind();
    m_shader.bind();

    // Pass objects by reference to draw command
    // (Assuming your Renderer::draw takes (VertexArray&, IndexBuffer&, Shader&))
    renderer.draw(m_va, m_ib, m_shader);
}

void SandboxLayer::onEvent(Core::Event &event)
{
}

void SandboxLayer::onDetach()
{
}
