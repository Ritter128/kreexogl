#version 450 core

layout(location = 0) in mediump vec3 aPosition;
layout(location = 1) in lowp    vec3 aColor;
layout(location = 2) in lowp    vec2 aTexCoords;

out lowp vec3 color;
out lowp vec2 texCoords;

uniform mediump mat4 uModelMatrix;
uniform mediump mat4 uViewMatrix;
uniform mediump mat4 uProjMatrix;

void main() 
{
  color = aColor;
  texCoords = aTexCoords;
  gl_Position = uProjMatrix * uViewMatrix * uModelMatrix * vec4(aPosition, 1.0);
}