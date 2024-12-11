#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Object.hpp"
#include "LightManager.hpp"

class UI {
public:
	UI(GLFWwindow* window);
	void hierarchy(double deltaTime, Object* root, LightManager* lightMan);
private:
	void hierarchyObjectUI(Object* obj, bool isRoot);
	void hierarchyLightUI(LightManager* lightMan);
	static const char* MaterialTypeToCString(Material::MaterialType type);
};