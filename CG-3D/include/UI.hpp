#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Object.hpp"
#include "LightManager.hpp"
#include "ImageLoader.hpp"

class UI {
public:
	UI(GLFWwindow* window);
	void begin();
	void hierarchy(double deltaTime, Object* root, LightManager* lightMan, ImageLoader* imgLoader);
	void textures(ImageLoader* textures);
	void selectedObject(Object* selected, ImageLoader* textures);
	void end();
private:
	void hierarchyObjectUI(Object* obj, bool isRoot, ImageLoader* imgLoader);
	void hierarchyLightUI(LightManager* lightMan);
	static const char* MaterialTypeToCString(Material::MaterialType type);
};