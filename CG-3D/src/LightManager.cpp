#include "LightManager.hpp"

LightManager::LightManager(){
	pointLights[0] = PointLight({0,0,0}, 10);
	pointLights[1] = PointLight({0,0,-10}, 10);
	ambientLightStrength = 1;
}

void LightManager::updateLights() {
	//Gourad
	GLuint id = Material::matTypeToId(Material::GOURAD);
	glUseProgram(id);
	glUniform3f(glGetUniformLocation(id, "lights[0].position"), pointLights[0].position.x, pointLights[0].position.y, pointLights[0].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[0].strength"), pointLights[0].strength);
	glUniform3f(glGetUniformLocation(id, "lights[1].position"), pointLights[1].position.x, pointLights[1].position.y, pointLights[1].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[1].strength"), pointLights[1].strength);
	glUniform1f(glGetUniformLocation(id, "ambientLightStrength"), ambientLightStrength);
	//Phong
	id = Material::matTypeToId(Material::PHONG);
	glUseProgram(id);
	glUniform3f(glGetUniformLocation(id, "lights[0].position"), pointLights[0].position.x, pointLights[0].position.y, pointLights[0].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[0].strength"), pointLights[0].strength);
	glUniform3f(glGetUniformLocation(id, "lights[1].position"), pointLights[1].position.x, pointLights[1].position.y, pointLights[1].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[1].strength"), pointLights[1].strength);
	glUniform1f(glGetUniformLocation(id, "ambientLightStrength"), ambientLightStrength);
	//Blinn-Phong
	id = Material::matTypeToId(Material::BLINN_PHONG);
	glUseProgram(id);
	glUniform3f(glGetUniformLocation(id, "lights[0].position"), pointLights[0].position.x, pointLights[0].position.y, pointLights[0].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[0].strength"), pointLights[0].strength);
	glUniform3f(glGetUniformLocation(id, "lights[1].position"), pointLights[1].position.x, pointLights[1].position.y, pointLights[1].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[1].strength"), pointLights[1].strength);
	glUniform1f(glGetUniformLocation(id, "ambientLightStrength"), ambientLightStrength);
}

glm::vec3 LightManager::getLightPosition(int index) {
	return pointLights[index].position;
}

void LightManager::setLightPosition(int index, glm::vec3 t) {
	pointLights[index].position = t;
}