#version 450 core

out lowp vec4 FragColor;

in lowp vec3 color;

void main() 
{
  FragColor = vec4(color, 1.0);
}