#include "LightManager.hpp"

LightManager::LightManager(){
	pointLights[0] = PointLight({0,0.5,0}, 10, {0,0,1,1});
	pointLights[1] = PointLight({0,0,-10}, 10, {1,1,0,1});
	ambientLightStrength = 1;
	for (int i = 0; i < LIGHT_COUNT; i++) {
		lightObjects[i] = ObjectConstructor::createLightObject(pointLights[i].position, pointLights[i].color);
	}
}

void LightManager::updateLights() {
	//update graphics side
	updateUniform(Material::matTypeToId(Material::GOURAD));
	updateUniform(Material::matTypeToId(Material::PHONG));
	updateUniform(Material::matTypeToId(Material::BLINN_PHONG));
	//update object representation
	for (int i = 0; i < LIGHT_COUNT; i++) {
		Transform t = lightObjects[i]->getTransform();
		t.worldPosition = pointLights[i].position;
		lightObjects[i]->setTransformAll(t);
		Material m = lightObjects[i]->getMaterial();
		m.baseColor = pointLights[i].color;
		lightObjects[i]->setMaterialAll(m);
	}
}

void LightManager::updateUniform(GLint id) {
	glUseProgram(id);
	glUniform3f(glGetUniformLocation(id, "lights[0].position"), pointLights[0].position.x, pointLights[0].position.y, pointLights[0].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[0].strength"), pointLights[0].strength);
	glUniform4f(glGetUniformLocation(id, "lights[0].color"), pointLights[0].color.r, pointLights[0].color.g, pointLights[0].color.b, pointLights[0].color.a);
	glUniform3f(glGetUniformLocation(id, "lights[1].position"), pointLights[1].position.x, pointLights[1].position.y, pointLights[1].position.z);
	glUniform1f(glGetUniformLocation(id, "lights[1].strength"), pointLights[1].strength);
	glUniform4f(glGetUniformLocation(id, "lights[1].color"), pointLights[1].color.r, pointLights[1].color.g, pointLights[1].color.b, pointLights[1].color.a);
	glUniform1f(glGetUniformLocation(id, "ambientLightStrength"), ambientLightStrength);
}

void LightManager::renderLights(Camera* camera) {
	for (int i = 0; i < LIGHT_COUNT; i++) {
		lightObjects[i]->render(camera);
	}
}

PointLight LightManager::getLight(int index) {
	return pointLights[index];
}

void LightManager::setLight(int index, PointLight light) {
	pointLights[index] = light;
}

LightManager::~LightManager() {
	for (int i = 0; i < LIGHT_COUNT; i++) {
		delete lightObjects[i];
	}
}