#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec3 v_Normal;
in vec3 v_Color; // The rainbow colors from C++
in vec2 v_TexCoord; // The UV coordinates (0,0 to 1,1)

// Uniforms
uniform sampler2D u_Texture; // The image slot (Slot 0)
uniform vec4 u_Color; // The Material color (Tint)

void main()
{
  // 1. Sample the texture using the UV coordinates
  vec4 texColor = texture(u_Texture, v_TexCoord);

  // 2. Mix it with the material tint (optional)
  // If you want the raw texture, just use 'texColor'
  color = texColor * u_Color;
}
