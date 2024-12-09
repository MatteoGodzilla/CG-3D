#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <assert.h>

namespace Error {
	//These Correspond to exit codes returned by the program
	enum ErrorCode {
		NO_ERROR,
		GLFW_CANNOT_INIT,
		GLFW_CANNOT_CREATE_WINDOW,
		GLAD_CANNOT_LOAD,
		SHADER_MAKER_COMPILE_ERROR,
		SHADER_MAKER_LINK_ERROR,
		SHADER_MAKER_CANNOT_OPEN_FILE,
		HERMITE_NOT_ENOUGH_POINTS,
		ASSIMP_SCENE_IS_NULL,
		ASSIMP_SCENE_IS_INCOMPLETE,
		ASSIMP_ROOT_IS_NULL,
		SHADER_UNIFORM_IS_INVALID,
		MATERIAL_TYPE_INVALID,
		STB_IMAGE_CANNOT_LOAD
	};
}

namespace ShaderCompiler {
	#define COMPILE_LOG_SIZE 512
	GLuint compile(const char* vertexShaderFile, const char* fragmentShaderFile);
}