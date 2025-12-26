#version 460 core

layout(location = 0) out vec4 color;

in vec3 v_color;

void main()
{
  color = vec4(1.0, 0.0, 0.0, 0.3);
};
