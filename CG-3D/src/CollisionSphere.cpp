#include "CollisionSphere.hpp"

CollisionSphere::CollisionSphere(glm::vec3 center, float radius) {
	updateCollisionSphere(center, radius);
}

void CollisionSphere::updateCollisionSphere(glm::vec3 center, float radius) {
	this->center = center;
	this->radius = radius;
}

bool CollisionSphere::isPointInsideCollisionSphere(glm::vec3 point) {
	glm::vec3 delta = point - center;
	return glm::dot(delta, delta) < radius * radius;
}

std::pair<glm::vec3, float> CollisionSphere::getBounds() {
	return std::make_pair(center, radius);
}