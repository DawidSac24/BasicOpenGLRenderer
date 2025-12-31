#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal; // Must be here to match C++ layout Index 1
layout(location = 2) in vec3 color; // Must be here to match C++ layout Index 2
layout(location = 3) in vec2 texCoord; // Must be here to match C++ layout Index 3

out vec2 v_TexCoord;

// 3. UNIFORMS
uniform mat4 u_viewProjection;
uniform mat4 u_model;

void main()
{
  // Pass the texture coordinate to the fragment shader
  v_TexCoord = texCoord;

  gl_Position = u_viewProjection * u_model * vec4(position, 1.0);
}
