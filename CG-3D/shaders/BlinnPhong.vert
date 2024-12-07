#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec4 worldPos;
out vec3 adjustedNormal;

//Transform of the object
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(){
    gl_Position = projMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    worldPos = worldMatrix * vec4(position, 1.0);
    adjustedNormal = normalize(mat3(transpose(inverse(worldMatrix))) * normal);
}