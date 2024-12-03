#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
public:
	glm::vec3 worldPosition = { 0.0, 0.0, 0.0 };
	glm::quat worldRotation = { };
	glm::vec3 worldScale = { 1.0, 1.0, 1.0 };
	glm::mat4 calculateMatrix();
};