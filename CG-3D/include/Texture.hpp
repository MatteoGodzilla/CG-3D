#pragma once
#include "glad/glad.h"

struct Texture {
	int width; 
	int height;
	int channels;
	GLuint texId;
};