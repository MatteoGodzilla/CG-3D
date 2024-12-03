#pragma once
#include "InputReceiver.hpp"
#include <stdio.h>

class InputDebugger : public InputReceiver {
public:
	void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) override {
		printf("%i %i %i %i\n", key, scancode, action, mods);
	}

	void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) override {
		printf("%i %i %i\n", button, action, mods);
	}

	void mousePosEvent(GLFWwindow* window, double xpos, double ypos) override {
		printf("%f %f\n", xpos, ypos);
	}
};