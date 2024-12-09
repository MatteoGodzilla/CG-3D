#version 330 core

in vec2 texUV;
out vec4 result;

uniform vec4 baseColor;
uniform sampler2D sample;

void main(){
    result = baseColor * texture(sample, texUV);
}