#include <GL/glew.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>

#include "Debug.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/buffers/IndexBuffer.h"
#include "Renderer/buffers/VertexArray.h"
#include "Renderer/buffers/VertexBuffer.h"
#include "Renderer/buffers/VertexBufferLayout.h"
#include "Window.h"
#include "glm/ext/matrix_clip_space.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    Core::WindowSpecification windowSpecification = {"OpenGL_renderer", 1280, 720, true, true};
    Core::Window window(windowSpecification);

    window.create();
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    Core::getOpenGLErrors();

    {
        float positions[] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, 1.0f, 0.0f,
                             0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 1.0f};

        unsigned int indices[]{0, 1, 2, 2, 3, 0};

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        Renderer::VertexArray va;
        Renderer::VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        Renderer::VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        Renderer::IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

        Renderer::Shader shader("../res/shaders/basic.vert", "../res/shaders/basic.frag");
        shader.bind();
        shader.setUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
        shader.setUniformMat4f("u_mvp", proj);

        Renderer::Texture texture("../res/textures/texture.png");
        texture.bind();
        // specify the texture slot as the second parameter
        shader.setUniform1i("u_texture", 0);

        float r = 0.0f;
        float increment = 0.05f;

        // Unbind everything for safety
        va.unbind();
        vb.unbind();
        ib.unbind();
        shader.unbind();

        Renderer::Renderer renderer;

        while (!window.shouldClose())
        {
            renderer.clear();

            shader.bind();
            shader.setUniform4f("u_color", r, 0.3f, 0.8f, 1.0f);

            renderer.draw(va, ib, shader);

            if (r > 1.0f)
            {
                increment = -0.05f;
            }
            else if (r < 0.0f)
            {
                increment = 0.05f;
            }
            r += increment;

            window.update();

            glfwPollEvents();
        }
        window.destroy();
    }
    glfwTerminate();
    return 0;
}
