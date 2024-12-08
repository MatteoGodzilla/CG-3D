#pragma once
#include <iostream>
#include "InputReceiver.hpp"
#include "Object.hpp"

class MaterialTypeSwitcher : public InputReceiver {
public:
	MaterialTypeSwitcher(Object* obj) {
		objReference = obj;
	}

	void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		if (key == GLFW_KEY_E) {
			Material m = objReference->getMaterial();
			m.updateType(action == GLFW_PRESS ? Material::PHONG : Material::BLINN_PHONG);
			objReference->setMaterial(m);
		}
	}

private:
	Object* objReference;
};