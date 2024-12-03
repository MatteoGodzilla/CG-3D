#include "Input.hpp"

//This is the meat of everything: a global vector of callbacks
static std::vector<InputReceiver*> callbacks;

void Input::init() {
	callbacks = std::vector<InputReceiver*>();
}

//---Begin of events called by GLFW---
void Input::receiveKeyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods) {
	for (size_t i = 0; i < callbacks.size(); i++) {
		callbacks.at(i)->keyboardEvent(window, key, scancode, action, mods);
	}
}

void Input::receiveMouseButtonEvents(GLFWwindow* window, int button, int action, int mods) {
	for (size_t i = 0; i < callbacks.size(); i++) {
		callbacks.at(i)->mouseButtonEvent(window, button, action, mods);
	}
}

void Input::receiveMousePosEvents(GLFWwindow* window, double xpos, double ypos) {
	for (size_t i = 0; i < callbacks.size(); i++) {
		callbacks.at(i)->mousePosEvent(window, xpos, ypos);
	}
}
//---End of events called by GLFW---

void Input::addConsumer(InputReceiver* callback) {
	callbacks.push_back(callback);
}