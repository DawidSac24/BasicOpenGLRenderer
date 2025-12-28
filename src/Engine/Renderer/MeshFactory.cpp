#include "MeshFactory.h"

#include <cmath> // Required for sin/cos
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

namespace Renderer
{

std::shared_ptr<Renderer::Mesh> MeshFactory::CreateCube()
{
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

    return std::make_shared<Renderer::Mesh>(vertices, indices);
}

// Helper constant for PI
const float PI = glm::pi<float>();

std::shared_ptr<Renderer::Mesh> MeshFactory::CreateSphere(int segments)
{
    std::vector<Renderer::Vertex> vertices;
    std::vector<uint32_t> indices;

    // --- 1. Generate Vertices (Latitude/Longitude) ---
    // Radius is 0.5f to match the cube size (Diameter = 1.0)
    float radius = 0.5f;

    for (int y = 0; y <= segments; ++y)
    {
        for (int x = 0; x <= segments; ++x)
        {
            // Calculate normalized UV coordinates [0.0 to 1.0]
            float xSegment = (float)x / (float)segments;
            float ySegment = (float)y / (float)segments;

            // Calculate angle positions
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            // Create the Vertex
            Renderer::Vertex v;

            // Position
            v.position = glm::vec3(xPos, yPos, zPos) * radius;

            // Normal (For a sphere, normal is just the normalized position)
            v.normal = glm::normalize(glm::vec3(xPos, yPos, zPos));

            // Color (White default)
            v.color = glm::vec3(1.0f, 1.0f, 1.0f); // Or vec4 depending on your struct

            // UV
            v.textUV = glm::vec2(xSegment, ySegment);

            vertices.push_back(v);
        }
    }

    // --- 2. Generate Indices (Triangles) ---
    // We connect the dots in a grid pattern
    for (int y = 0; y < segments; ++y)
    {
        for (int x = 0; x < segments; ++x)
        {
            indices.push_back((y + 1) * (segments + 1) + x); // Bottom Left
            indices.push_back(y * (segments + 1) + x); // Top Left
            indices.push_back(y * (segments + 1) + x + 1); // Top Right

            indices.push_back((y + 1) * (segments + 1) + x); // Bottom Left
            indices.push_back(y * (segments + 1) + x + 1); // Top Right
            indices.push_back((y + 1) * (segments + 1) + x + 1); // Bottom Right
        }
    }

    return std::make_shared<Renderer::Mesh>(vertices, indices);
}

std::shared_ptr<Renderer::Mesh> MeshFactory::CreatePlane()
{
    // A simple 1x1 flat plane on the XZ axis, facing UP (Y+)
    std::vector<Renderer::Vertex> vertices = {
        // Position            Normal              Color               UV
        { { -0.5f, 0.0f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } }, // Bottom-Left
        { { 0.5f, 0.0f, 0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } }, // Bottom-Right
        { { 0.5f, 0.0f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } }, // Top-Right
        { { -0.5f, 0.0f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } } // Top-Left
    };

    std::vector<uint32_t> indices = {
        0, 1, 2, // First Triangle
        2, 3, 0 // Second Triangle
    };

    return std::make_shared<Renderer::Mesh>(vertices, indices);
}
}
