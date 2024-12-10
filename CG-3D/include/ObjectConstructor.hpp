#pragma once
#include "Object.hpp"

namespace ObjectConstructor {
	Object* createLightObject(glm::vec3 worldPosition, glm::vec4 color);
	Object* createUnitCube();
	Object* createRay(glm::vec3 worldPosition, glm::vec3 direction);
};