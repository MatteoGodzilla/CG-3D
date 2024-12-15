#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>

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
#include "CollisionManagerInput.hpp"

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
	GLFWwindow* window = glfwCreateWindow(1024, 768, "CG-3D", NULL, NULL);
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
	imgLoader.loadCubemap(
		"textures/skybox/v2/side.png",
		"textures/skybox/v2/side.png",
		"textures/skybox/v2/top.png",
		"textures/skybox/v2/bottom.png",
		"textures/skybox/v2/front.png",
		"textures/skybox/v2/side.png"
	);
	
	Camera cam = Camera();
	Input::addConsumer(&cam);

	CollisionManager collManager = CollisionManager(&cam);
	CollisionManagerInput collManagerInput = CollisionManagerInput(&collManager);
	Input::addConsumer(&collManagerInput);

	Object* scene = new Object("Scene root");

	//Basic plane
	auto begin = std::chrono::steady_clock::now();
	Object* plane = ObjectConstructor::createSubdividedPlane(150, 150);
	Transform planeTransform = Transform();
	planeTransform.worldPosition = glm::vec3(0, 0, 0);
	planeTransform.worldScale = glm::vec3(150,1,150);
	plane->setTransformSelf(planeTransform);
	scene->addChild(plane);
	Material m = Material(Material::UNLIT_TEXTURE);
	m.baseColor = glm::vec4(1, 1, 1, 1);
	m.texture = imgLoader.getTexture("textures/checkerboard.png");
	plane->setMaterialSelf(m);
	collManager.addObject(plane);
	std::cout << "[Scene] Created " << plane->name << std::endl;

	//Red teapot
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
	red.cubemap = imgLoader.getCubemap();
	red.reflectivity = 0.2f;
	teapot->setMaterialAll(red);
	collManager.addObject(teapot);
	scene->addChild(teapot);
	std::cout << "[Scene] Created " << teapot->name << std::endl;

	//Green teapot
	Object* teapot2 = AssimpConverter::loadObject("objs/teapot.obj");
	teapot2->name = "Teapot 2";
	Transform t2 = Transform();
	t2.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::half_pi<float>(), glm::vec3(1, 0, 0));
	t2.worldScale = glm::vec3(1.0) / 4.0f;
	t2.worldPosition = glm::vec3(0, 2, 0);
	teapot2->setTransformAll(t2);
	Material green = Material(Material::BLINN_PHONG);
	green.baseColor = glm::vec4(0.0, 1.0, 0.0, 1.0);
	green.ambientColor = glm::vec4(0.0, 0.25, 0.0, 1.0);
	green.diffuseColor = glm::vec4(0, 1, 0, 1.0);
	green.specularColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	green.cubemap = imgLoader.getCubemap();
	green.reflectivity = 0.2f;
	teapot2->setMaterialAll(green);
	collManager.addObject(teapot2);
	scene->addChild(teapot2);
	std::cout << "[Scene] Created " << teapot2->name << std::endl;

	//Blue teapot
	Object* teapot3 = AssimpConverter::loadObject("objs/teapot.obj");
	teapot3->name = "Teapot 3";
	Transform t3 = Transform();
	t3.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), glm::pi<float>(), glm::vec3(0, 1, 0));
	t3.worldScale = glm::vec3(1.0) / 4.0f;
	t3.worldPosition = glm::vec3(0, 0, 2);
	teapot3->setTransformAll(t3);
	Material blue = Material(Material::BLINN_PHONG);
	blue.baseColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
	blue.ambientColor = glm::vec4(0.0, 0.0, 0.25, 1.0);
	blue.diffuseColor = glm::vec4(0, 0, 1, 1.0);
	blue.specularColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	blue.cubemap = imgLoader.getCubemap();
	blue.reflectivity = 0.2f;
	teapot3->setMaterialAll(blue);
	collManager.addObject(teapot3);
	scene->addChild(teapot3);
	std::cout << "[Scene] Created " << teapot3->name << std::endl;

	//Big teapot 
	Object* bigTeapot = AssimpConverter::loadObject("objs/teapot.obj");
	bigTeapot->name = "Big teapot";
	Transform bigTeapotTransform = Transform();
	bigTeapotTransform.worldRotation = glm::rotate(glm::quat(1.0, 0.0, 0.0, 0.0), 5.0f / 4.0f * glm::pi<float>(), glm::vec3(0, 1, 0));
	bigTeapotTransform.worldRotation = glm::rotate(bigTeapotTransform.worldRotation, -glm::quarter_pi<float>(), glm::vec3(1, 0, 0));
	bigTeapotTransform.worldScale = glm::vec3(1.0);
	bigTeapotTransform.worldPosition = glm::vec3(-7, 4, 10);
	bigTeapot->setTransformAll(bigTeapotTransform);
	Material bigTeapotMaterial = Material(Material::BLINN_PHONG);
	bigTeapotMaterial.baseColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	bigTeapotMaterial.ambientColor = glm::vec4(0.25, 0.25, 0.25, 1.0);
	bigTeapotMaterial.diffuseColor = glm::vec4(0.4, 0.4, 0.4, 1.0);
	bigTeapotMaterial.specularColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	bigTeapotMaterial.cubemap = imgLoader.getCubemap();
	bigTeapotMaterial.reflectivity = 0.2f;
	bigTeapot->setMaterialAll(bigTeapotMaterial);
	collManager.addObject(bigTeapot);
	scene->addChild(bigTeapot);
	std::cout << "[Scene] Created " << teapot3->name << std::endl;

	//Teacup
	Object* teacup = AssimpConverter::loadObject("objs/teacup.obj");
	teacup->name = "Teacup";
	Transform teacupTransform = Transform();
	teacupTransform.worldPosition = glm::vec3(-4, 1, 13);
	teacupTransform.worldRotation = glm::rotate(teacupTransform.worldRotation, glm::quarter_pi<float>(), glm::vec3(0, 1, 0));
	teacupTransform.worldRotation = glm::rotate(teacupTransform.worldRotation, -0.25f * glm::quarter_pi<float>(), glm::vec3(1, 0, 0));
	teacup->setTransformAll(teacupTransform);
	teacup->setMaterialAll(bigTeapotMaterial);
	scene->addChild(teacup);
	collManager.addObject(teacup);
	std::cout << "[Scene] Created " << teacup->name << std::endl;

	//David
	Object* head = AssimpConverter::loadObject("objs/david.obj");
	head->name = "David";
	Transform headTransform = Transform();
	headTransform.worldPosition = glm::vec3(5, 0, -10);
	//headTransform.worldRotation = glm::rotate(headTransform.worldRotation, 0.0f, glm::vec3(0, 1, 0));
	head->setTransformAll(headTransform);
	Material headMaterial = Material(Material::BLINN_PHONG);
	headMaterial.ambientColor = glm::vec4(0.235, 0.235, 0.235, 1);
	headMaterial.diffuseColor = glm::vec4(0.463, 0.463, 0.463, 1);
	headMaterial.specularColor = glm::vec4(1, 1, 1, 1);
	headMaterial.shininess = 128;
	headMaterial.reflectivity = 0.15f;
	headMaterial.cubemap = imgLoader.getCubemap();
	head->setMaterialAll(headMaterial);
	collManager.addObject(head);
	scene->addChild(head);
	std::cout << "[Scene] Created " << head->name << std::endl;

	//Column
	Object* column = AssimpConverter::loadObject("objs/column.obj");
	column->name = "Column";
	Transform columnTransform = Transform();
	columnTransform.worldPosition = glm::vec3(-10, 0, -20);
	column->setTransformAll(columnTransform);
	Material columnMaterial = Material(Material::UNLIT_TEXTURE);
	columnMaterial.baseColor = glm::vec4(0.8, 0.8, 0.8, 1);
	columnMaterial.texture = imgLoader.getTexture("textures/marble-2398946.jpg");
	column->setMaterialAll(columnMaterial);
	collManager.addObject(column);
	scene->addChild(column);
	std::cout << "[Scene] Created " << column->name << std::endl;

	//Mountain
	Object* mountainWireframe = AssimpConverter::loadObject("objs/mountain.obj");
	mountainWireframe->name = "Mountain Wireframe";
	Material mountainWireframeMaterial = Material(Material::UNLIT_WIREFRAME);
	mountainWireframeMaterial.baseColor = glm::vec4(1, 1, 0, 1);
	mountainWireframe->setMaterialAll(mountainWireframeMaterial);
	
	Object* mountainFill = AssimpConverter::loadObject("objs/mountain.obj");
	mountainFill->name = "Mountain Fill";
	Material mountainFillMaterial = Material(Material::UNLIT);
	mountainFillMaterial.baseColor = glm::vec4(0.1, 0.0, 0.3, 1);
	mountainFill->setMaterialAll(mountainFillMaterial);
	
	Object* mountain = new Object("Mountain");
	mountain->addChild(mountainFill);
	mountain->addChild(mountainWireframe);
	Transform mountainTransform = Transform();
	mountainTransform.worldPosition = glm::vec3(30, 0, 60);
	mountainTransform.worldRotation = glm::rotate(mountainTransform.worldRotation, glm::two_pi<float>(), glm::vec3(0, 1, 0));
	mountainTransform.worldScale = glm::vec3(10,10,10);
	mountain->setTransformAll(mountainTransform);
	scene->addChild(mountain);
	std::cout << "[Scene] Created " << mountain->name << std::endl;

	//Flip flops 
	Object* flipFlop = AssimpConverter::loadObject("objs/flip-flop.obj");
	flipFlop->name = "Flip flop";
	Transform flipFlopTransform = Transform();
	flipFlopTransform.worldPosition = glm::vec3(10, 5, 5);
	flipFlopTransform.worldScale = glm::vec3(3,3,3);
	Material flipFlopMaterial = Material(Material::GOURAD);
	flipFlopMaterial.baseColor = glm::vec4(0, 0.5, 0, 1);
	flipFlopMaterial.ambientColor = glm::vec4(0, 0.25, 0, 1);
	flipFlopMaterial.diffuseColor = glm::vec4(0, 0.5, 0, 1);
	flipFlopMaterial.specularColor = glm::vec4(0, 0, 0, 1);
	flipFlopMaterial.reflectivity = 0;
	flipFlop->setMaterialAll(flipFlopMaterial);
	scene->addChild(flipFlop);
	//collManager.addObject(flipFlop);
	std::cout << "[Scene] Created " << flipFlop->name << std::endl;

	//Pig
	Object* pig = AssimpConverter::loadObject("objs/pig.obj");
	pig->name = "Pig";
	Transform pigTransform = Transform();
	pigTransform.worldScale = glm::vec3(0.25, 0.25, 0.25);
	pigTransform.worldPosition = glm::vec3(0, 40, 0);
	pig->setTransformAll(pigTransform);
	Material pigMaterial = Material(Material::BLINN_PHONG);
	pigMaterial.ambientColor = glm::vec4(0.682, 0.195, 0.573, 1);
	pigMaterial.diffuseColor = glm::vec4(0.682, 0.195, 0.573, 1);
	pigMaterial.specularColor = glm::vec4(0.3, 0.3, 0.3, 1);
	pigMaterial.shininess = 1; 
	pigMaterial.reflectivity = 0;
	pigMaterial.cubemap = imgLoader.getCubemap();
	pig->setMaterialAll(pigMaterial);
	scene->addChild(pig);
	std::cout << "[Scene] Created " << pig->name << std::endl;

	//a e s t e t h i c
	Object* aestethic = AssimpConverter::loadObject("objs/aestethic.obj");
	aestethic->name = "A E S T E T H I C";
	Transform aestethicTransform = Transform();
	aestethicTransform.worldPosition = glm::vec3(-10, 5, 0);
	aestethicTransform.worldRotation = glm::rotate(aestethicTransform.worldRotation, glm::half_pi<float>(), glm::vec3(0, 1, 0));
	aestethicTransform.worldScale = glm::vec3(5,5,5);
	aestethic->setTransformAll(aestethicTransform);
	Material aestethicMaterial = Material(Material::BLINN_PHONG);
	aestethicMaterial.baseColor = glm::vec4(0, 0, 0, 0);
	aestethicMaterial.ambientColor = glm::vec4(0, 0, 0, 0);
	aestethicMaterial.diffuseColor = glm::vec4(0, 0, 0, 0);
	aestethicMaterial.specularColor = glm::vec4(0, 0, 0, 0);
	aestethicMaterial.shininess = 1;
	aestethicMaterial.reflectivity = 0.9;
	aestethicMaterial.cubemap = imgLoader.getCubemap();
	aestethic->setMaterialAll(aestethicMaterial);
	scene->addChild(aestethic);
	collManager.addObject(aestethic);
	std::cout << "[Scene] Created " << aestethic->name << std::endl;

	//Skybox
	Object* skybox = ObjectConstructor::createUnitCube();
	skybox->name = "Skybox";
	Material skyboxM = Material(Material::UNLIT_CUBEMAP);
	skyboxM.baseColor = glm::vec4(1, 1, 1, 1);
	skyboxM.cubemap = imgLoader.getCubemap();
	skybox->setMaterialAll(skyboxM);
	scene->addChild(skybox);
	std::cout << "[Scene] Created " << skybox->name << std::endl;
	auto end = std::chrono::steady_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "[Scene] Created scene in " << (float)duration.count()/1000 << " seconds" << std::endl;

	LightManager lightManager = LightManager();

	UI gui = UI(window);
	//---END GAME OBJECTS---

	//---ANIMATION VALUES---
	glm::vec3 bigTeapotCenter = bigTeapotTransform.worldPosition;
	glm::vec3 teacupCenter = teacupTransform.worldPosition;
	glm::vec3 bigDisplacement = glm::vec3(0, 1, 0);
	glm::vec3 smallDisplacement = glm::vec3(0, 0.25, 0);

	glm::vec3 pigCenter = pigTransform.worldPosition;
	float pigHorizontalRadius = 20;
	float pigVerticalRadius = 5;

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

		//---ANIMATIONS---

		bigTeapotTransform.worldPosition = bigTeapotCenter + (float)sin(nowFrame) * bigDisplacement;
		bigTeapot->setTransformAll(bigTeapotTransform);

		teacupTransform.worldPosition = teacupCenter + (float)cos(nowFrame) * smallDisplacement;
		teacup->setTransformAll(teacupTransform);

		flipFlopTransform.worldRotation = glm::rotate(flipFlopTransform.worldRotation, (float)deltaTime * 1, glm::vec3(0, 1, 0));
		flipFlopTransform.worldRotation = glm::rotate(flipFlopTransform.worldRotation, (float)deltaTime * 1.414f, glm::vec3(1, 0, 0));
		flipFlopTransform.worldRotation = glm::rotate(flipFlopTransform.worldRotation, (float)deltaTime * 0.667f, glm::vec3(0, 0, 1));

		flipFlop->setTransformAll(flipFlopTransform);

		float pigAngle = (float)nowFrame / 10;
		pigTransform.worldPosition = pigCenter + pigHorizontalRadius * glm::vec3(cos(pigAngle), 0, sin(pigAngle));
		pigTransform.worldPosition += pigVerticalRadius * glm::vec3(0, sin(pigAngle * 1.414f), 0);
		pigTransform.worldRotation = glm::rotate(glm::quat(1, 0, 0, 0), glm::half_pi<float>() - pigAngle, glm::vec3(0, 1, 0));
		pigTransform.worldRotation = glm::rotate(pigTransform.worldRotation, -cos(pigAngle * 1.414f)/5, glm::vec3(0, 0, 1));
		pig->setTransformAll(pigTransform);

		//---PHYSICS---

		collManager.updateCollisions();
		collManager.resolveCollisions();

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