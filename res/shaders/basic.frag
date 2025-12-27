#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_textCoord;
in vec3 v_color;

void main()
{
  // Use the vertex color passed from C++
  // If v_color is (0,0,0) or dark, we can force a fallback:
  // color = vec4(1.0, 0.0, 0.0, 1.0);

  color = vec4(v_color, 0.0);
};
