// #include <GLFW/glfw3.h> // Assuming you use GLFW
// #include <glad/glad.h>
// #include <vector>
//
// #include "Engine/Camera.h"
// #include "Engine/Mesh.h"
// #include "Renderer/Shader.h"
// #include "Renderer/Texture.h"
//
// int main()
// {
//     // 1. Initialize Window (GLFW/GLAD boilerplate)
//     // ... (Your window creation code here) ...
//
//     // CRITICAL: Enable Depth Testing
//     glEnable(GL_DEPTH_TEST);
//
//     // 2. Define the Cube Data
//     // We need 24 vertices (4 per face x 6 faces) to have sharp corners.
//     // If you share vertices, the lighting (normals) will look smooth/spherical.
//     std::vector<Renderer::Vertex> vertices = {
//         // Front Face (Normal 0,0,1)
//         { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } }, // Bottom-Left
//         { { 0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }, // Bottom-Right
//         { { 0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } }, // Top-Right
//         { { -0.5f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } }, // Top-Left
//
//         // Back Face (Normal 0,0,-1) ... (You would add the other 5 faces here)
//         // For testing, just 1 face (a square) is enough to verify it works!
//     };
//
//     std::vector<GLuint> indices = {
//         0, 1, 2, 2, 3, 0 // Front face
//         // Add indices for other faces if you added vertices
//     };
//
//     // 3. EMPTY Texture List
//     std::vector<Renderer::Texture> noTextures;
//
//     // 4. Use the new "SolidColor" shader
//     Renderer::Shader whiteShader("res/shaders/SolidColor.shader");
//     Engine::Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
//
//     // 5. Create Mesh with empty textures
//     Engine::Mesh cubeMesh(vertices, indices, noTextures);
//
//     while (!window.closed())
//     {
//         renderer.Clear();
//
//         // Standard Camera Updates
//         camera.Inputs(window);
//         camera.Matrix(whiteShader, "u_Projection");
//
//         // Set Model Matrix (Identity)
//         whiteShader.bind(); // Make sure shader is bound before setting uniforms!
//         whiteShader.setUniformMat4f("u_Model", glm::mat4(1.0f));
//
//         // Draw
//         cubeMesh.draw(whiteShader, camera);
//
//         window.SwapBuffers();
//         glfwPollEvents();
//     }
//
//     return 0;
// }
