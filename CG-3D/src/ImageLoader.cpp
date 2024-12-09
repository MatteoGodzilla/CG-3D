#include "ImageLoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ImageLoader::ImageLoader() {
	textures = std::unordered_map<std::string, Texture*>();
}

Texture* ImageLoader::getTexture(std::string path) {
	if (textures.contains(path)) {
		return textures.at(path);
	}
	else {
		Texture* t = loadTexture(path);
		textures.insert(std::make_pair(path, t));
		return t;
	}
}

Texture* ImageLoader::loadTexture(std::string path) {
	Texture* t = new Texture();
	unsigned char *data = stbi_load(path.c_str(), &t->width, &t->height, &t->channels, 0);
	
	glGenTextures(1, &t->texId);
	glBindTexture(GL_TEXTURE_2D, t->texId);
	//these might need to be changed in runtime
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int storeType = t->channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t->width, t->height, 0, storeType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return t;
}

ImageLoader::~ImageLoader() {
	for (auto& pair : textures) {
		delete pair.second;
	}
}