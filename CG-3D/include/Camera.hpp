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

	void update(double deltaTime, float aspect);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	CollisionSphere getCollision();
	std::pair<glm::vec3, glm::vec3> getSelectionRay();
	
	glm::vec3 worldPosition;
private:
	enum CameraMode {
		FPS,TRACKBALL
	};
	CameraMode mode;

	//variables used for fps mode
	float yaw; //horizontal
	float pitch; //vertical
	glm::vec2 lastMousePos;

	//variables used for trackball mode
	glm::vec2 dragStart;
	bool trackBallin;

	//variables for collision 
	CollisionSphere collision;
	float collisionRadius = 0.5;

	//movement directions
	int rightMovement = 0;
	int forwardMovement = 0;
	int upwardMovement = 0;

	float aspect;

	//selection 
	glm::vec3 selectionPosition;
	glm::vec3 selectionDirection;
};