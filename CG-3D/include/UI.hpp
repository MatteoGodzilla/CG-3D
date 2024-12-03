#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>
#include <iostream>
#include <string>
#include <deque>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Transform.hpp"

class UI {
public:
	UI(GLFWwindow* window);
	void render(double deltaTime);

	//---GETTERS---
	//float getCameraSize();
	//int getHistorySize();
	//double getTimeBetweenUpdates();
	//float getMaxPlayerSpeed();

	//Set up from main
	//std::deque<size_t>* activeBoidGraph;
	//size_t activeBoidCount;
	//glm::vec2 flockCenter;
	//glm::vec2 flockSpeed;
	//glm::vec2 playerPos;
	//glm::vec2 playerSpeed;
private:
	//float orthoSize = 20;
	//int historySize = 50;
	//float timeBetweenUpdates = 0.5;
	//float maxPlayerSpeed = 5;
};