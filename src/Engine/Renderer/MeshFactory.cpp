#include "MeshFactory.h"

#include "Engine/Core/AssetManager.h"

#include <cmath> // Required for sin/cos
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Renderer
{

std::shared_ptr<Mesh> MeshFactory::create(Engine::EntityType type, int segments /* = 32 */)
{
    switch (type)
    {
    case Engine::EntityType::Unknown:
        break;
    case Engine::EntityType::Empty:
        break;
    case Engine::EntityType::Cube:
        return createCube();
    case Engine::EntityType::Sphere:
        return createSphere(segments);
    case Engine::EntityType::Plane:;
        return createPlane();
    case Engine::EntityType::Camera:
        break;
    case Engine::EntityType::Count:
        break;
    }

    std::cerr << "Mesh creation error: invalid Entity Type" << std::endl;
    return nullptr;
}

std::shared_ptr<Material> MeshFactory::getDefaultMaterial()
{
    auto shader = Core::AssetManager::getShader("defaultShader");
    if (!shader)
    {
        std::cerr << "CRITICAL: 'BasicShader' missing!" << std::endl;
    }

    auto texture = Core::AssetManager::getTexture("defaultTexture");
    if (!texture)
    {
        std::cerr << "CRITICAL: 'GreyTexture' missing!" << std::endl;
    }
    std::string matName = "defaultMaterial";
    auto material = std::make_shared<Material>(matName, shader);

    material->setTexture("u_Texture", texture);
    material->setFloat4("u_Color", { 1.0f, 1.0f, 1.0f, 1.0f });
    return material;
}

std::shared_ptr<Mesh> MeshFactory::createCube()
{
    std::vector<Vertex> vertices = {
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

    std::string meshName = "Cube";
    return std::make_shared<Renderer::Mesh>(meshName, vertices, indices);
}

// Helper constant for PI
const float PI = glm::pi<float>();

std::shared_ptr<Mesh> MeshFactory::createSphere(int segments)
{
    std::vector<Renderer::Vertex> vertices;
    std::vector<uint32_t> indices;

    float radius = 0.5f;

    for (int y = 0; y <= segments; ++y)
    {
        for (int x = 0; x <= segments; ++x)
        {
            float xSegment = (float)x / (float)segments;
            float ySegment = (float)y / (float)segments;

            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            Vertex v;

            v.position = glm::vec3(xPos, yPos, zPos) * radius;

            v.normal = glm::normalize(glm::vec3(xPos, yPos, zPos));

            v.color = glm::vec3(1.0f, 1.0f, 1.0f);
            v.textUV = glm::vec2(xSegment, ySegment);

            vertices.push_back(v);
        }
    }

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

    std::string meshName = "Sphere";
    return std::make_shared<Mesh>(meshName, vertices, indices);
}

std::shared_ptr<Mesh> MeshFactory::createPlane()
{
    std::vector<Vertex> vertices = {
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

    std::string meshName = "Plane";
    return std::make_shared<Mesh>(meshName, vertices, indices);
}
}
