#include "CollisionBox.hpp"

CollisionBox::CollisionBox() {
	min = glm::vec3(0, 0, 0);
	max = glm::vec3(0, 0, 0);
}

void CollisionBox::updateCollisionBoxFromPoints(std::vector<glm::vec3>& points) {
	if (points.size() > 0) {
		min = max = points.at(0);
		for (size_t i = 1; i < points.size(); i++) {
			glm::vec3 point = points.at(i);
			min.x = std::min(min.x, point.x);
			min.y = std::min(min.y, point.y);
			min.z = std::min(min.z, point.z);

			max.x = std::max(max.x, point.x);
			max.y = std::max(max.y, point.y);
			max.z = std::max(max.z, point.z);
		}
	}
	else {
		min = max = glm::vec3(0, 0, 0);
	}
}

bool CollisionBox::isPointInside(glm::vec3 point){
	return min.x <= point.x <= max.x &&
		min.y <= point.y <= max.y &&
		min.z <= point.z <= max.z;
}

bool CollisionBox::isCollisionBoxInside(CollisionBox* other) {
	return min.x <= other->max.x &&
		max.x >= other->min.x &&
		min.y <= other->max.y &&
		max.y >= other->min.y &&
		min.z <= other->max.z &&
		max.z >= other->min.z;
}

glm::vec3 CollisionBox::clampPointToBounds(glm::vec3 point) {
	float x = std::min(std::max(min.x, point.x), max.x);
	float y = std::min(std::max(min.y, point.y), max.y);
	float z = std::min(std::max(min.z, point.z), max.z);
	return glm::vec3(x, y, z);
}

std::pair<glm::vec3, glm::vec3> CollisionBox::getBounds() {
	return std::make_pair(min, max);
}