#pragma once
#include <iostream>
#include <unordered_map>
#include "glad/glad.h"
#include "Texture.hpp"
#include "Utils.hpp"

class ImageLoader {
public:
	ImageLoader();
	Texture* getTexture(std::string path);
	void loadCubemap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void setTextureFilter(Texture* t, GLint minFilter, GLint maxFilter);
	void setTextureWrap(Texture* t, GLint horizontalWrap, GLint verticalWrap);

	Cubemap* getCubemap();
	std::unordered_map<std::string, Texture*>& getTextures();
	~ImageLoader();
private:
	Texture* loadTexture(std::string path, GLint target = GL_TEXTURE_2D);
	//references to textures in vram
	std::unordered_map<std::string, Texture*> textures;	
	Cubemap cubemap;
};