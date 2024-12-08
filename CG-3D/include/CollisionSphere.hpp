#pragma once
#include "glm/glm.hpp"

class CollisionSphere {
public:
	CollisionSphere(glm::vec3 center, float radius);
	void updateCollisionSphere(glm::vec3 center, float radius);
	bool isPointInsideCollisionSphere(glm::vec3 point);

	std::pair<glm::vec3, float> getBounds();
private:
	glm::vec3 center;
	float radius;
};