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
	t.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), -glm::half_pi<float>(), glm::vec3(0, 1, 0));
	t.worldScale = glm::vec3(1.0) / 4.0f;
	t.worldPosition = glm::vec3(2, 0, 0);
	teapot->setTransform(t);
	Material red = Material();
	red.ambientColor = glm::vec4(1.0, 0.0, 0.0, 1.0);
	teapot->setMaterial(red);

	Object* teapot2 = AssimpConverter::loadObject("objs/teapot.obj");
	Transform t2 = Transform();
	t2.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::half_pi<float>(), glm::vec3(1, 0, 0));
	t2.worldScale = glm::vec3(1.0) / 4.0f;
	t2.worldPosition = glm::vec3(0, 2, 0);
	teapot2->setTransform(t2);
	Material green = Material();
	green.ambientColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
	teapot2->setMaterial(green);

	Object* teapot3 = AssimpConverter::loadObject("objs/teapot.obj");
	Transform t3 = Transform();
	t3.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::pi<float>(), glm::vec3(0, 1, 0));
	t3.worldScale = glm::vec3(1.0) / 4.0f;
	t3.worldPosition = glm::vec3(0, 0, 2);
	teapot3->setTransform(t3);
	Material blue = Material();
	blue.ambientColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
	teapot3->setMaterial(blue);

	UI gui = UI(window);
	//---END GAME OBJECTS---

	//Setup Opengl flags
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	//Main loop
	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//---UPDATE LOGIC---		
		double nowFrame = glfwGetTime();
		double deltaTime = nowFrame - lastFrame;

		cam.update(deltaTime);
		//Transform t = teapot3->getTransform();
		//t.worldRotation = glm::rotate(t.worldRotation, glm::pi<float>() * (float)deltaTime, glm::vec3(0, 1, 0));
		//teapot3->setTransform(t);

		lastFrame = nowFrame;

		//---UPDATE GRAPHICS---
		
		

		//---RENDERING LOGIC---
		//clear screen
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		teapot->render(&cam);
		teapot2->render(&cam);
		teapot3->render(&cam);
			
		//render gui overlay
		gui.render(deltaTime);

		glfwSwapBuffers(window);
	}

	Material::destroyShaders();
	delete teapot;
	delete teapot2;
	delete teapot3;

	//Close GLFW
	glfwTerminate();
}