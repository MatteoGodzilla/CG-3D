#include "Transform.hpp"

glm::mat4 Transform::calculateMatrix() {
	glm::mat4 pos = glm::translate(glm::mat4(1.0), worldPosition);
	glm::mat4 scale = glm::scale(glm::mat4(1.0), worldScale);
	glm::mat4 rotation = glm::mat4_cast(worldRotation);
	
	//following the rotation order in unity: ZXY
	/*
	glm::mat4 rotation = glm::mat4(1.0);
	rotation = glm::rotate(rotation, worldRotation.z, glm::vec3(0, 0, 1));
	rotation = glm::rotate(rotation, worldRotation.x, glm::vec3(1, 0, 0));
	rotation = glm::rotate(rotation, worldRotation.y, glm::vec3(0, 1, 0));
	*/

	return pos * rotation * scale;
}