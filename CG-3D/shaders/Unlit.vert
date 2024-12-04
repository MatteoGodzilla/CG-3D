#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 uv;

out vec4 col;

void main(){
    gl_Position = vec4(position.z, position.y - 1, -position.x, 4.0);
    col = color;
}