#version 330 core

layout(location = 0) out vec4 color;

// 1. INPUTS (From Vertex Shader)
in vec2 v_TexCoord; // Now this matches the Vertex Shader output!

// 2. UNIFORMS
uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
  // Sample texture
  vec4 texColor = texture(u_Texture, v_TexCoord);

  // Apply tint and output
  color = texColor * u_Color;
}
