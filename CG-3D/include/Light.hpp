#pragma once
#include "glm/glm.hpp"

//This represents a point light
struct Light {
	glm::vec3 position;
	glm::vec4 color = {1.0, 1.0, 1.0, 1.0};
	float strenght = 1;
};