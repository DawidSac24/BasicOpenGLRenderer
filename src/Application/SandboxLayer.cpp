#include "SandboxLayer.h"

#include "Engine/Camera.h"
#include "Engine/Core/Application.h"
#include "Engine/Maths/Transform.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include <memory>

SandboxLayer::SandboxLayer()
{
    Core::Application& application = Core::Application::get();
    glm::vec2 frameBufferSize = application.getWindow()->getFrameBufferSize();

    std::vector<Renderer::Vertex> vertices = {
        // Front Face (Normal 0, 0, 1)
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, // Bottom-Left
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // Bottom-Right
        { { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } }, // Top-Right
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }, // Top-Left

        // Back Face (Normal 0, 0, -1)
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f } }, // Bottom-Left (from back)
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // Bottom-Right
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } }, // Top-Right
        { { 0.5f, 0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }, // Top-Left

        // Left Face (Normal -1, 0, 0)
        { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { -0.5f, -0.5f, 0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { -0.5f, 0.5f, 0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Right Face (Normal 1, 0, 0)
        { { 0.5f, -0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Top Face (Normal 0, 1, 0)
        { { -0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, 0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },

        // Bottom Face (Normal 0, -1, 0)
        { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
        { { 0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
        { { 0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } },
        { { -0.5f, -0.5f, 0.5f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
    };
    // 36 Indices (6 faces * 2 triangles * 3 indices)
    std::vector<GLuint> indices = {
        0, 1, 2, 2, 3, 0, // Front
        4, 5, 6, 6, 7, 4, // Back
        8, 9, 10, 10, 11, 8, // Left
        12, 13, 14, 14, 15, 12, // Right
        16, 17, 18, 18, 19, 16, // Top
        20, 21, 22, 22, 23, 20 // Bottom
    };
    std::vector<GLuint> lineIndices = { // Front Face
        0, 1, 1, 2, 2, 3, 3, 0,
        // Back Face
        4, 5, 5, 6, 6, 7, 7, 4,
        // Left Face
        8, 9, 9, 10, 10, 11, 11, 8,
        // Right Face
        12, 13, 13, 14, 14, 15, 15, 12,
        // Top Face
        16, 17, 17, 18, 18, 19, 19, 16,
        // Bottom Face
        20, 21, 21, 22, 22, 23, 23, 20
    };

    // EMPTY Texture List
    std::vector<Renderer::Texture> noTextures;

    whiteShader
        = std::make_unique<Renderer::Shader>("../res/shaders/whiteShader.vert", "../res/shaders/whiteShader.frag");
    basicShader = std::make_unique<Renderer::Shader>("../res/shaders/basic.vert", "../res/shaders/basic.frag");
    camera = std::make_unique<Engine::Camera>(frameBufferSize.x, frameBufferSize.y, glm::vec3(0.0f, 0.0f, 2.0f));
    cubeMesh = std::make_unique<Engine::Mesh>(vertices, indices, noTextures);
    cubeLineMesh = std::make_unique<Engine::Mesh>(vertices, lineIndices, noTextures);
}
SandboxLayer::~SandboxLayer() { }

void SandboxLayer::onUpdate()
{
    m_rotation += 0.5f;
    {
        Math::Transform& cameraTransform = camera->transform;

        ImGui::Begin("Camera"); // Create a window called "Hello, world!" and append into it.
        //
        // ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)
        // ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
        // ImGui::Checkbox("Another Window", &show_another_window);

        glm::vec3 cameraPos = cameraTransform.getPosition();

        ImGui::SliderFloat("x", &cameraPos.x, -10.0f, 10.0f);
        ImGui::SliderFloat("y", &cameraPos.y, -10.0f, 10.0f);
        ImGui::SliderFloat("z", &cameraPos.z, -10.0f, 10.0f);

        cameraTransform.setPosition(cameraPos);

        ImGui::Text("Rotation");
        // Step A: Convert Quaternion -> Euler Angles (Radians)
        glm::vec3 eulerRadians = glm::eulerAngles(cameraTransform.getRotation());

        // Step B: Convert Radians -> Degrees (For humans to read in ImGui)
        glm::vec3 eulerDegrees = glm::degrees(eulerRadians);

        // Step C: Edit the DEGREES with ImGui
        // We use a helper bool to see if any slider changed
        bool rotationChanged = false;
        rotationChanged |= ImGui::DragFloat("Pitch (X)", &eulerDegrees.x, 0.5f);
        rotationChanged |= ImGui::DragFloat("Yaw   (Y)", &eulerDegrees.y, 0.5f);
        rotationChanged |= ImGui::DragFloat("Roll  (Z)", &eulerDegrees.z, 0.5f);

        // Step D: If changed, convert Degrees -> Radians -> Quaternion and save back
        if (rotationChanged)
        {
            glm::vec3 finalRadians = glm::radians(eulerDegrees);
            cameraTransform.setRotation(glm::quat(finalRadians));
        }
        // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        // if (ImGui::Button(
        //         "Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        //     counter++;
        // ImGui::SameLine();
        // ImGui::Text("counter = %d", counter);
        //
        // ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // // 3. Show another simple window.
    // if (show_another_window)
    // {
    //     ImGui::Begin(
    //         "Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a
    //                                                  // closing button that will clear the bool when clicked)
    //     ImGui::Text("Hello from another window!");
    //     if (ImGui::Button("Close Me"))
    //         show_another_window = false;
    //     ImGui::End();
    // }
}

void SandboxLayer::onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update rotation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    // --- PASS 1: DRAW WHITE LINES ---
    {
        whiteShader->bind();
        camera->matrix(*whiteShader.get(), "u_camMatrix");

        // Scale slightly (1.001) to sit on top of the solid cube
        glm::mat4 borderModel = glm::scale(model, glm::vec3(1.001f, 1.001f, 1.001f));
        whiteShader->setUniformMat4f("u_model", borderModel);

        // Don't use glPolygonMode here.
        // We draw the "cubeLineMesh" using GL_LINES.
        cubeLineMesh->draw(renderer, *whiteShader.get(), GL_LINES);
    }

    // --- PASS 2: DRAW TRANSPARENT INTERIOR ---
    {
        basicShader->bind();
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthMask(GL_FALSE);

        camera->matrix(*basicShader.get(), "u_camMatrix");
        basicShader->setUniformMat4f("u_model", model);

        // Draw the normal mesh using GL_TRIANGLES
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        cubeMesh->draw(renderer, *basicShader.get(), GL_TRIANGLES);

        glDepthMask(GL_TRUE);
    }
}

void SandboxLayer::onEvent(Core::Event& event) { }

void SandboxLayer::onDetach() { }
