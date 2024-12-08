#pragma once
#include "Transform.hpp"
#include "InputReceiver.hpp"
#include "CollisionSphere.hpp"

class Camera : public InputReceiver{
public:
	Camera();
	void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) override;

	void mousePosEvent(GLFWwindow* window, double xpos, double ypos) override;

	void update(double deltaTime);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	void setWorldPos(glm::vec3 worldPos);
	CollisionSphere getCollision();
	
	glm::vec3 worldPosition;
private:
	float yaw; //horizontal
	float pitch; //vertical
	glm::vec2 lastMousePos;

	CollisionSphere collision;
	float collisionRadius = 0.5;

	int rightMovement = 0;
	int forwardMovement = 0;
	int upwardMovement = 0;
};