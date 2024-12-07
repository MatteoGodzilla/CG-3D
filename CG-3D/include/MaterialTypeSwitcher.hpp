#pragma once
#include <iostream>
#include "InputReceiver.hpp"
#include "Material.hpp"

class MaterialTypeSwitcher : public InputReceiver {
public:
	MaterialTypeSwitcher(Material* mat) {
		matReference = mat;
	}

	void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		matReference->updateType(
			glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS 
			? Material::BLINN_PHONG 
			: Material::PHONG
		);
	}

private:
	Material* matReference;
};