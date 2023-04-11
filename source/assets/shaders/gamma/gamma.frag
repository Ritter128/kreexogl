#version 450 core 

out vec4 FragColor;

in vec3 color;
in vec2 texCoords;

uniform sampler2D uTexSample;

void main() {
    float gamma = 2.2;

    FragColor = vec4(color * pow(texture(uTexSample, texCoords).rgb, vec3(1.0/gamma)), 1.0);
}