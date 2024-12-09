#pragma once
#include <unordered_map>
#include "glad/glad.h"
#include "Texture.hpp"

class ImageLoader {
public:
	ImageLoader();
	Texture* getTexture(std::string path);
	~ImageLoader();
private:
	Texture* loadTexture(std::string path);
	//references to textures in vram
	std::unordered_map<std::string, Texture*> textures;
};