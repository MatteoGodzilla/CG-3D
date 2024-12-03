#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>

#include "InputReceiver.hpp"

//this class only does input forwarding, nothing else
//actual input logic is split into each class that derives InputReceiver
class Input {
public:
	Input() = delete;
	static void init();
	static void receiveKeyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void receiveMouseButtonEvents(GLFWwindow* window, int button, int action, int mods);
	static void receiveMousePosEvents(GLFWwindow* window, double xpos, double ypos);
	static void addConsumer(InputReceiver* callback);
};
