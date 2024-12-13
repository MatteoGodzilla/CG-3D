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

Texture* ImageLoader::loadTexture(std::string path, GLint target) {
	Texture* t = new Texture();
	unsigned char *data = stbi_load(path.c_str(), &t->width, &t->height, &t->channels, 0);
	if (data == nullptr) {
		std::cerr << "[ImageLoader] There was an error loading texture " << path << "(" << target << ")" << std::endl;
		//exit(Error::STB_IMAGE_CANNOT_LOAD);
	}

	glGenTextures(1, &t->texId);
	glBindTexture(target, t->texId);
	//these might need to be changed in runtime
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int storeType = t->channels == 3 ? GL_RGB : GL_RGBA;
	glTexImage2D(target, 0, GL_RGBA, t->width, t->height, 0, storeType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(target);

	stbi_image_free(data);
	return t;
}

void ImageLoader::loadCubemap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) {
	cubemap = Cubemap();

	glGenTextures(1, &cubemap.cubemapId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.cubemapId);

	cubemap.right = loadTexture(right, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	cubemap.left = loadTexture(left, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	cubemap.top = loadTexture(top, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	cubemap.bottom = loadTexture(bottom, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	cubemap.front = loadTexture(front, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	cubemap.back = loadTexture(back, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void ImageLoader::setTextureFilter(Texture* t, GLint minFilter, GLint magFilter) {
	glBindTexture(GL_TEXTURE_2D, t->texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void ImageLoader::setTextureWrap(Texture* t, GLint horizontalWrap, GLint verticalWrap) {
	glBindTexture(GL_TEXTURE_2D, t->texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, horizontalWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, verticalWrap);
}

Cubemap* ImageLoader::getCubemap() {
	return &cubemap;
}

std::unordered_map<std::string, Texture*>& ImageLoader::getTextures() {
	return textures;
}

ImageLoader::~ImageLoader() {
	for (auto& pair : textures) {
		delete pair.second;
	}
}