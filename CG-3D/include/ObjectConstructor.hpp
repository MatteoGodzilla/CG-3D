#pragma once
#include "Object.hpp"

namespace ObjectConstructor {
	Object* createLightObject(glm::vec3 worldPosition, glm::vec4 color);
	Object* createUnitCube();
	Object* createRay(glm::vec3 worldPosition, glm::vec3 direction);
	Object* createUnitPyramid();
	Object* createUnitSphere(int latResolution, int lonResolution);
	Object* createUnitCylinder(int circleResolution);
	Object* createUnitCone(int circleResolution);
	Object* createTorus(float outerRadius, float sliceRadius, int outerResolution, int sliceResolution);
};