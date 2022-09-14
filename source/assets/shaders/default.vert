#version 450 core

layout(location = 0) in mediump vec3 aPosition;
layout(location = 1) in lowp    vec3 aColor;

out lowp vec3 color;

uniform mediump mat4 uModelMatrix;
uniform mediump mat4 uViewMatrix;
uniform mediump mat4 uProjMatrix;

void main() 
{
  color = aColor;
  gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);
}