#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils.hpp"
#include "UI.hpp"
#include "Input.hpp"
#include "InputDebugger.hpp"
#include "Transform.hpp"
#include "Object.hpp"
#include "AssimpConverter.hpp"
#include "Camera.hpp"

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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Input::init();

	glfwMakeContextCurrent(window);
	//Load GLAD (must be done after setting the context) 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return Error::GLAD_CANNOT_LOAD;
	}

	//---BEGIN GAME OBJECTS---
	Material::initShaders();
	
	Camera cam = Camera();
	Input::addConsumer(&cam);

	Object* teapot = AssimpConverter::loadObject("objs/teapot.obj");
	Transform t = Transform();
	t.worldRotation = glm::rotate(teapot->transform.worldRotation, glm::pi<float>() / 2, glm::vec3(0, 1, 0));
	t.worldScale = glm::vec3(1.0) / 4.0f;
	t.worldPosition = glm::vec3(0, -1, 0);
	teapot->setTransform(t);

	UI gui = UI(window);
	//---END GAME OBJECTS---

	//Enable transparency effects (needed for the background)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable Depth testing
	glEnable(GL_DEPTH_TEST);

	//Main loop
	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//---UPDATE LOGIC---		
		double nowFrame = glfwGetTime();
		double deltaTime = nowFrame - lastFrame;

		cam.update(deltaTime);

		lastFrame = nowFrame;
		//t.worldRotation = glm::rotate(t.worldRotation, (float)(glm::pi<double>() * deltaTime), glm::vec3(1, 1, 1));
		//teapot->setTransform(t);

		//---UPDATE GRAPHICS---
		
		teapot->updateGraphics(&cam);

		//---RENDERING LOGIC---
		//clear screen
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		teapot->render();

		//render gui overlay
		gui.render(deltaTime);

		glfwSwapBuffers(window);
	}

	//Close GLFW
	glfwTerminate();
}