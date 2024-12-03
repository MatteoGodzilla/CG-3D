#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

//Treat this as an interface, when it technically isn't one
//There are default implementations in here so that we don't force derived classes to override everything
//but only what they need 
class InputReceiver {
public:
	virtual void keyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {}

	virtual void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods) {}

	virtual void mousePosEvent(GLFWwindow* window, double xpos, double ypos) {}
}; 
