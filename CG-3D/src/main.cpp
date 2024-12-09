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
#include "LightManager.hpp"
#include "MaterialTypeSwitcher.hpp"
#include "ObjectConstructor.hpp"
#include "CollisionManager.hpp"
#include "ImageLoader.hpp"

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

	glfwMakeContextCurrent(window);
	//Load GLAD (must be done after setting the context) 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return Error::GLAD_CANNOT_LOAD;
	}

	//---BEGIN GAME OBJECTS---
	Material::initShaders();
	ImageLoader imgLoader = ImageLoader();
	
	Camera cam = Camera();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Input::addConsumer(&cam);

	CollisionManager collManager = CollisionManager(&cam);

	Object* teapot = AssimpConverter::loadObject("objs/teapot.obj");
	Transform t = Transform();
	t.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), -glm::half_pi<float>(), glm::vec3(0, 1, 0));
	t.worldScale = glm::vec3(1.0)/4.0f;
	t.worldPosition = glm::vec3(2, 0, 0);
	teapot->setTransform(t);
	Material red = Material(Material::BLINN_PHONG);
	red.baseColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
	red.ambientColor = glm::vec4(0.25, 0.0, 0.0, 1.0);
	red.diffuseColor = glm::vec4(1, 0, 0, 1.0);
	red.specularColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	teapot->setMaterial(red);
	collManager.addObject(teapot);

	MaterialTypeSwitcher matSwitcher = MaterialTypeSwitcher(teapot);
	Input::addConsumer(&matSwitcher);

	Object* teapot2 = AssimpConverter::loadObject("objs/teapot.obj");
	Transform t2 = Transform();
	t2.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::half_pi<float>(), glm::vec3(1, 0, 0));
	t2.worldScale = glm::vec3(1.0) / 4.0f;
	t2.worldPosition = glm::vec3(0, 2, 0);
	teapot2->setTransform(t2);
	Material green = Material(Material::UNLIT_TEXTURE);
	green.baseColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
	green.texture = imgLoader.getTexture("textures/checkerboard.jpg");
	teapot2->setMaterial(green);
	collManager.addObject(teapot2);

	Object* teapot3 = AssimpConverter::loadObject("objs/teapot.obj");
	Transform t3 = Transform();
	t3.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::pi<float>(), glm::vec3(0, 1, 0));
	t3.worldScale = glm::vec3(1.0) / 4.0f;
	t3.worldPosition = glm::vec3(0, 0, 2);
	teapot3->setTransform(t3);
	Material blue = Material(Material::UNLIT);
	blue.baseColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
	teapot3->setMaterial(blue);
	collManager.addObject(teapot3);

	Object* skybox = ObjectConstructor::createSkybox();
	Material skyboxM = Material(Material::UNLIT_CUBEMAP);
	skyboxM.baseColor = glm::vec4(1, 1, 1, 1);
	skyboxM.cubemap = imgLoader.loadCubemap(
		"textures/skybox/right.jpg",
		"textures/skybox/left.jpg",
		"textures/skybox/top.jpg",
		"textures/skybox/bottom.jpg",
		"textures/skybox/front.jpg",
		"textures/skybox/back.jpg"
	);
	skybox->setMaterial(skyboxM);

	LightManager lightManager = LightManager();

	Object* light1 = ObjectConstructor::createLightObject(lightManager.getLight(0).position, lightManager.getLight(0).color);
	Object* light2 = ObjectConstructor::createLightObject(lightManager.getLight(1).position, lightManager.getLight(1).color);

	UI gui = UI(window);
	//---END GAME OBJECTS---

	//Setup Opengl flags
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	//Main loop
	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		//---UPDATE LOGIC---		
		double nowFrame = glfwGetTime();
		double deltaTime = nowFrame - lastFrame;

		cam.update(deltaTime);
		collManager.updateCollisions();
		collManager.resolveCollisions();
		
		Transform t = teapot->getTransform();
		t.worldRotation = glm::rotate(t.worldRotation, 1.0f * (float)deltaTime, glm::vec3(0, 1, 0));
		teapot->setTransform(t);
		teapot->updateCollisionBox();

		PointLight a = lightManager.getLight(0);
		a.color = glm::vec4(cos(nowFrame), sin(nowFrame), 0, 1);
		lightManager.setLight(0, a);

		PointLight b = lightManager.getLight(1);
		b.position = glm::vec3(5 * cos(nowFrame), 0, 5 * sin(nowFrame));
		lightManager.setLight(1, b);

		lastFrame = nowFrame;

		//---RENDERING LOGIC---
		//clear screen
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightManager.updateLights();
		lightManager.renderLights(&cam);
		teapot->render(&cam);
		teapot2->render(&cam);
		teapot3->render(&cam);
		skybox->render(&cam);
			
		//render gui overlay
		gui.render(deltaTime);

		glfwSwapBuffers(window);
	}

	Material::destroyShaders();
	delete teapot;
	delete teapot2;
	delete teapot3;
	delete skybox;
	delete light1;
	delete light2;

	//Close GLFW
	glfwTerminate();
}