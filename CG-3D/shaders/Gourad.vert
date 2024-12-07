#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec4 col;

//Transform of the object
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

//Material properties of the object
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

//Lighting information (Set up by Light Manager)
struct PointLight{
    vec3 position;
    float strength;
};

#define LIGHT_NUM 2
uniform PointLight lights[LIGHT_NUM];
uniform float ambientLightStrength;
uniform vec3 cameraWorldPos;

void main(){
    gl_Position = projMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    vec4 worldPos = worldMatrix * vec4(position, 1.0);

    vec3 adjustedNormal = normalize(mat3(transpose(inverse(worldMatrix))) * normal);

    //start off with some ambient color by default
    vec4 result = ambientColor * ambientLightStrength;

    for(int i = 0; i < LIGHT_NUM; i++){
        vec3 worldPosToLight = normalize(lights[i].position - worldPos.xyz);
        vec3 worldPosToCamera = normalize(cameraWorldPos - worldPos.xyz);
        //diffuse pass
        float diffusePerc = max(dot(worldPosToLight, adjustedNormal),0);
        result += diffuseColor * diffusePerc;

        //specular pass
        vec3 reflectionVec = normalize(2 * dot(worldPosToLight, adjustedNormal) * adjustedNormal - worldPosToLight);
        float specularPerc = pow(max(dot(reflectionVec, worldPosToCamera),0), lights[i].strength);
        result += specularColor * specularPerc;
    }

    col = vec4(result.xyz,1.0);
}