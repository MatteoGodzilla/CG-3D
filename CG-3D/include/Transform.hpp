#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
public:
	glm::vec3 worldPosition = { 0.0, 0.0, 0.0 };
	//can be changed to a glm::vec3 in order to use euler angles
	//glm::vec3 worldRotation = { 0.0, 0.0, 0.0 };
	glm::quat worldRotation = { 1.0, 0.0, 0.0, 0.0 };
	glm::vec3 worldScale = { 1.0, 1.0, 1.0 };
	glm::mat4 calculateMatrix();
};