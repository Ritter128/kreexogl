#version 450 core

layout(location = 0) in mediump vec3 aPosition;
layout(location = 1) in lowp    vec3 aColor;

out lowp vec3 color;

lowp float angle = 1.0;

uniform mediump mat4 uModelMatrix;

void main() 
{

  color = aColor;
  gl_Position = uModelMatrix * vec4(aPosition, 1.0);
}