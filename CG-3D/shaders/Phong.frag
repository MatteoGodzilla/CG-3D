#version 330 core

in vec4 worldPos;
in vec3 adjustedNormal;

out vec4 result;

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
    //start off with some ambient color by default
    result = ambientColor * ambientLightStrength;
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
    result.a = 1;
}