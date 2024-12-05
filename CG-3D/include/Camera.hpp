#pragma once
#include "Transform.hpp"
#include "InputReceiver.hpp"

class Camera : public InputReceiver{
public:
	Camera();
	void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) override;

	void mousePosEvent(GLFWwindow* window, double xpos, double ypos) override;

	void update(double deltaTime);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
private:
	glm::vec3 position;
	float yaw; //horizontal
	float pitch; //vertical
	glm::vec2 lastMousePos;

	int rightMovement = 0;
	int forwardMovement = 0;
	int upwardMovement = 0;
};