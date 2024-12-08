#pragma once
#include "glad/glad.h"
#include "PointLight.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "ObjectConstructor.hpp"

#define LIGHT_COUNT 2

class LightManager {
public:
	LightManager();
	void updateLights();
	PointLight getLight(int index);
	void setLight(int index, PointLight light);
	void renderLights(Camera* camera);
	~LightManager();

private:
	void updateUniform(GLint id);
	PointLight pointLights[LIGHT_COUNT];
	Object* lightObjects[LIGHT_COUNT];
	float ambientLightStrength;
};