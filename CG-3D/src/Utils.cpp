#include "Utils.hpp"

static void compileSingleShader(GLuint shaderID, const char* transfer) {
	GLint success;
	glShaderSource(shaderID, 1, &transfer, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success) {
		//abort
		GLchar buffer[COMPILE_LOG_SIZE];
		glGetShaderInfoLog(shaderID, COMPILE_LOG_SIZE, NULL, buffer);
		std::cerr << "[ShaderCompiler] Compile error: " << buffer << std::endl;
		exit(Error::SHADER_MAKER_COMPILE_ERROR); //yea ik this is brutal
	}
}

static std::string readEntireFile(const char* file) {
	std::ifstream readingFile(file);
	if (!readingFile.is_open()) {
		//abort
		std::cerr << "[ShaderCompiler] Cannot open file " << file << ". Aborting" << std::endl;
		exit(Error::SHADER_MAKER_CANNOT_OPEN_FILE);
	}
	//This code is ugly, but it just allocates space in the string and then reads everything into that
	readingFile.seekg(0, std::ios::end);
	size_t bytes = readingFile.tellg();
	std::string result(bytes, ' ');
	readingFile.seekg(0, std::ios::beg);
	readingFile.read(&result[0], bytes);
	return result;
}

GLuint ShaderCompiler::compile(const char* vertexShaderFile, const char* fragmentShaderFile) {
	//Vertex Shader
	std::string vertexShaderSource = readEntireFile(vertexShaderFile);
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	compileSingleShader(vertexShaderID, vertexShaderSource.c_str());

	//Fragment Shader
	std::string fragmentShaderSource = readEntireFile(fragmentShaderFile);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	compileSingleShader(fragmentShaderID, fragmentShaderSource.c_str());

	//Compile final program
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShaderID);
	glAttachShader(program, fragmentShaderID);
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		//abort
		GLchar buffer[COMPILE_LOG_SIZE];
		glGetProgramInfoLog(program, COMPILE_LOG_SIZE, NULL, buffer);
		std::cerr << "[ShaderCompiler] Link error: " << buffer << std::endl;
		exit(Error::SHADER_MAKER_LINK_ERROR);
	}

	//If the program has compiled successfully, we don't need the source code for the shaders anymore
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return program;
}