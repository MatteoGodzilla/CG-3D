#include "Transform.hpp"

glm::mat4 Transform::calculateMatrix() {
	glm::mat4 pos = glm::translate(glm::mat4(1.0), worldPosition);
	glm::mat4 scale = glm::scale(glm::mat4(1.0), worldScale);
	glm::mat4 rotation = glm::mat4_cast(worldRotation);
	return scale * rotation * pos;
}