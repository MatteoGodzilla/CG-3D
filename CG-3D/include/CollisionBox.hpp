#pragma once
#include "Transform.hpp"

class CollisionBox {
public:
	CollisionBox();
	void updateCollisionBoxFromPoints(std::vector<glm::vec3>& points);

	bool isPointInside(glm::vec3 point);
	bool isCollisionBoxInside(CollisionBox* other);
	glm::vec3 clampPointToBounds(glm::vec3 point);
	std::pair<glm::vec3, glm::vec3> getBounds();
private:
	glm::vec3 min;
	glm::vec3 max;
	//actual values needed for collision
};