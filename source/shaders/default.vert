#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 color;

float angle = 1;

vec2 mapPos;

mat2 m = mat2(
    cos(angle), -sin(angle), 
    sin(angle), cos(angle)
);

void main() 
{
  mapPos = vec2(aPosition);

  color = aColor;
  gl_Position = vec4(m * mapPos, 0.0, 1.0);
}