#pragma once
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "Material.hpp"

//They emit white light
struct PointLight {
	glm::vec3 position;
	float strength;
};

class LightManager {
public:
	LightManager();
	void updateLights();
	glm::vec3 getLightPosition(int index);
	void setLightPosition(int index, glm::vec3 t);

private:
	PointLight pointLights[2];
	float ambientLightStrength;
};