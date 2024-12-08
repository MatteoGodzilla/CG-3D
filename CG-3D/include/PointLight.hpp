#pragma once
#include "glm/glm.hpp"

struct PointLight {
	glm::vec3 position;
	float strength;
	glm::vec4 color;
};