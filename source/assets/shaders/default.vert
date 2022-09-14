#version 450 core

layout(location = 0) in mediump vec3 aPosition;
layout(location = 1) in lowp    vec3 aColor;

out lowp vec3 color;

lowp float angle = 1.0;

mediump vec2 mapPos;

mediump mat2 m = mat2(
    cos(angle), -sin(angle), 
    sin(angle), cos(angle)
);

void main() 
{
  mapPos = vec2(aPosition);

  color = aColor;
  gl_Position = vec4(m * mapPos, 0.0, 1.0);
}