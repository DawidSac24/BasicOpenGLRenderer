#version 330 core

layout(location = 0) in vec3 position;
// We don't need normals/colors for the outline, so we can ignore loc 1,2,3

// Renderer standard naming
uniform mat4 u_viewProjection; 
uniform mat4 u_model;

void main()
{
    gl_Position = u_viewProjection * u_model * vec4(position, 1.0);
}
