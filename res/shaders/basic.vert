#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textCoord;

out vec2 v_textCoord;

void main()
{
  gl_Position = position;
  v_textCoord = textCoord;
};
