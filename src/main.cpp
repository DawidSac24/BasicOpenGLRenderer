#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>

#include "Debug.h"
#include "Window.h"
#include "renderer/Shader.h"
#include "renderer/buffers/IndexBuffer.h"
#include "renderer/buffers/VertexArray.h"
#include "renderer/buffers/VertexBuffer.h"
#include "renderer/buffers/VertexBufferLayout.h"

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
    getOpenGLErrors();

    {
        float positions[] = {
            -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f,
        };

        unsigned int indices[]{0, 1, 2, 2, 3, 0};

        Renderer::VertexArray va;
        Renderer::VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        Renderer::VertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        Renderer::IndexBuffer ib(indices, 6);

        std::string vertexSource = Renderer::parseShader("../res/shaders/basic.vert");
        std::string fragmentSource = Renderer::parseShader("../res/shaders/basic.frag");

        unsigned int shader = Renderer::createShader(vertexSource, fragmentSource);
        glUseProgram(shader);

        // *** assigning variables from cpu to gpu (on the shader) ***
        // we first retrieve the location of the variable (uniform of 4 floats here)
        // we can ask opengl to get the location by name:
        int location = glGetUniformLocation(shader, "u_color");
        // the assert is optional in most cases, bc the variable may get 'stashed' by opengl when it is not used etc
        assert(location != -1);
        glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

        float r = 0.0f;
        float increment = 0.05f;

        // Unbind everything for safety
        glBindVertexArray(0);
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        while (!window.shouldClose())
        {
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shader);
            glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

            va.bind();
            ib.bind();

            // We specify the count as the number of INDICES not vertexes!!!
            // don't have to reference the indices bc we did it in (so we put nullptr) :
            // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
        glDeleteProgram(shader);
        window.destroy();
    }
    glfwTerminate();
    return 0;
}
