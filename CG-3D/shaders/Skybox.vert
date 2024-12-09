#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 direction;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(){
    direction = position;
    vec4 pos = projMatrix * mat4(mat3(viewMatrix)) * vec4(position, 1.0);
    gl_Position = pos.xyww; //tricks opengl in putting the skybox as fas as possible
}