#pragma once
#include "glad/glad.h"

struct Texture {
	int width; 
	int height;
	int channels;
	GLuint texId;
};

struct Cubemap {
	Texture* left;
	Texture* right;
	Texture* top;
	Texture* bottom;
	Texture* front;
	Texture* back;
	GLuint cubemapId;
};