#pragma once
#include <iostream>
#include "InputReceiver.hpp"
#include "CollisionManager.hpp"

class CollisionManagerInput : public InputReceiver {
public:
	CollisionManagerInput(CollisionManager* cm) {
		collManager = cm;
	}

	void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		if (key == GLFW_KEY_C && action == GLFW_PRESS) {
			collManager->showCollisionBoxes = !collManager->showCollisionBoxes;
			//Material m = objReference->getMaterial();
			//m.type = (action == GLFW_PRESS ? Material::PHONG : Material::BLINN_PHONG);
			//objReference->setMaterialAll(m);
		}
	}

private:
	CollisionManager* collManager;
};