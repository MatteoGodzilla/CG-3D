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

	Object* scene = new Object("Scene root");

	Object* teapot = AssimpConverter::loadObject("objs/teapot.obj");
	teapot->name = "Teapot 1";
	Transform t = Transform();
	t.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), -glm::half_pi<float>(), glm::vec3(0, 1, 0));
	t.worldScale = glm::vec3(1.0)/4.0f;
	t.worldPosition = glm::vec3(2, 0, 0);
	teapot->setTransformAll(t);
	Material red = Material(Material::BLINN_PHONG);
	red.baseColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
	red.ambientColor = glm::vec4(0.25, 0.0, 0.0, 1.0);
	red.diffuseColor = glm::vec4(1, 0, 0, 1.0);
	red.specularColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	teapot->setMaterialAll(red);
	collManager.addObject(teapot);
	
	scene->addChild(teapot);

	MaterialTypeSwitcher matSwitcher = MaterialTypeSwitcher(teapot);
	Input::addConsumer(&matSwitcher);

	Object* teapot2 = AssimpConverter::loadObject("objs/teapot.obj");
	teapot2->name = "Teapot 2";
	Transform t2 = Transform();
	t2.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::half_pi<float>(), glm::vec3(1, 0, 0));
	t2.worldScale = glm::vec3(1.0) / 4.0f;
	t2.worldPosition = glm::vec3(0, 2, 0);
	teapot2->setTransformAll(t2);
	Material green = Material(Material::UNLIT_TEXTURE);
	green.baseColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
	green.texture = imgLoader.getTexture("textures/checkerboard.jpg");
	teapot2->setMaterialAll(green);
	collManager.addObject(teapot2);

	scene->addChild(teapot2);

	Object* teapot3 = AssimpConverter::loadObject("objs/teapot.obj");
	teapot3->name = "Teapot 3";
	Transform t3 = Transform();
	t3.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::pi<float>(), glm::vec3(0, 1, 0));
	t3.worldScale = glm::vec3(1.0) / 4.0f;
	t3.worldPosition = glm::vec3(0, 0, 2);
	teapot3->setTransformAll(t3);
	Material blue = Material(Material::UNLIT);
	blue.baseColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
	teapot3->setMaterialAll(blue);
	collManager.addObject(teapot3);

	scene->addChild(teapot3);

	Object* skybox = ObjectConstructor::createUnitCube();
	skybox->name = "Skybox";
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
	skybox->setMaterialAll(skyboxM);

	scene->addChild(skybox);

	Object* pyramid = ObjectConstructor::createUnitPyramid();
	Transform pyramidTransform = Transform();
	pyramidTransform.worldPosition = glm::vec3(5, 2, 4);
	pyramidTransform.worldRotation = glm::rotate(pyramidTransform.worldRotation, glm::quarter_pi<float>(), glm::vec3(0, 1, 0));
	pyramid->setTransformAll(pyramidTransform);
	scene->addChild(pyramid);
	collManager.addObject(pyramid);

	Object* sphere = ObjectConstructor::createTorus(8,1,20,20);
	scene->addChild(sphere);
	collManager.addObject(sphere);

	LightManager lightManager = LightManager();

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

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		cam.update(deltaTime, (float)width / (float)height);
		collManager.updateCollisions();
		collManager.resolveCollisions();

		teapot->updateCollisionBox();
		teapot2->updateCollisionBox();
		teapot3->updateCollisionBox();

		Object* selected = collManager.getSelectedObject();

		lastFrame = nowFrame;

		//---RENDERING LOGIC---
		//clear screen
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightManager.updateLights();
		lightManager.renderLights(&cam);
		scene->render(&cam);
		collManager.renderCollisions(&cam);
			
		//render gui overlay
		gui.begin();
		gui.hierarchy(deltaTime, scene, &lightManager, &imgLoader);
		gui.textures(&imgLoader);
		gui.selectedObject(selected);
		gui.end();

		glfwSwapBuffers(window);
	}

	Material::destroyShaders();
	delete scene;

	//Close GLFW
	glfwTerminate();
}