#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec4 col;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform vec4 baseColor;

void main(){
    gl_Position = projMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    col = vec4(normal, 1.0);
}