#version 460 core

// MUST match the order in Mesh.cpp layout.push()
layout(location = 0) in vec3 position; // was vec4, but you push 3 floats in C++
layout(location = 1) in vec3 normal;   // Newly added to match C++ (Mesh loc 1)
layout(location = 2) in vec3 color;    // Match C++ (Mesh loc 2)
layout(location = 3) in vec2 textCoord;// Match C++ (Mesh loc 3)

out vec2 v_textCoord;
out vec3 v_color;

// Renderer::submit sends these specific names
uniform mat4 u_viewProjection;
uniform mat4 u_model;

void main()
{
    // Multiply VP * Model * Position
    gl_Position = u_viewProjection * u_model * vec4(position, 1.0);
    
    v_textCoord = textCoord;
    v_color = color;
};
