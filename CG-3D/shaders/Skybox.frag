#version 330 core

in vec3 direction;
out vec4 result;

uniform vec4 baseColor;
uniform samplerCube cubemap;

void main(){
    result = baseColor * texture(cubemap, direction);
}