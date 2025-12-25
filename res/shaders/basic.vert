#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;
layout(location = 2) in vec3 color;

out vec2 v_textCoord;
out vec3 v_color;

uniform mat4 u_mvp;

void main()
{
  gl_Position = u_mvp * position;
  v_textCoord = textCoord;
  v_color = color;
};
