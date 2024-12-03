#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ErrorCode.hpp"
#include "UI.hpp"
#include "Input.hpp"
#include "InputDebugger.hpp"
#include "Transform.hpp"

#include "assimp/Importer.hpp"

void resizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	//Init GLFW
	if (!glfwInit())
		return Error::GLFW_CANNOT_INIT;

	//Set window hints
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create GLFW Window
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Poggers", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return Error::GLFW_CANNOT_CREATE_WINDOW;
	}

	//Set up callbacks for events
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetKeyCallback(window, Input::receiveKeyboardEvents);
	glfwSetCursorPosCallback(window, Input::receiveMousePosEvents);
	glfwSetMouseButtonCallback(window, Input::receiveMouseButtonEvents);
	Input::init();
	InputDebugger dbg = InputDebugger();
	Input::addConsumer(&dbg);

	glfwMakeContextCurrent(window);
	//Load GLAD (must be done after setting the context) 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return Error::GLAD_CANNOT_LOAD;
	}

	//---BEGIN GAME OBJECTS---
	UI gui = UI(window);
	Assimp::Importer importer;
	
	//---END GAME OBJECTS---

	//Enable transparency effects (needed for the background)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Main loop
	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//---UPDATE LOGIC---		
		double nowFrame = glfwGetTime();
		double deltaTime = nowFrame - lastFrame;

		//---UPDATE GRAPHICS---

		
		//---RENDERING LOGIC---
		//clear screen
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//render gui overlay
		gui.render(deltaTime);

		glfwSwapBuffers(window);
	}

	//Close GLFW
	glfwTerminate();
}