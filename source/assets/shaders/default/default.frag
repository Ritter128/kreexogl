#version 450 core

out lowp vec4 FragColor;

in lowp vec3 color;
in lowp vec2 texCoords;

uniform sampler2D uTexSample;

void main() 
{
  FragColor = texture(uTexSample, texCoords) * vec4(color, 1.0);
}