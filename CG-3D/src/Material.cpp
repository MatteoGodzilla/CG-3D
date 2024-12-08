#include "Material.hpp"

//because c++ is a dumb language and these need to be defined somewhere 
GLuint Material::unlitShaderId;
GLuint Material::gouradShaderId;
GLuint Material::phongShaderId;
GLuint Material::blinnPhongShaderId;

void Material::initShaders() {
	unlitShaderId = ShaderCompiler::compile("shaders/Unlit.vert", "shaders/Unlit.frag");
	gouradShaderId = ShaderCompiler::compile("shaders/Gourad.vert", "shaders/Gourad.frag");
	phongShaderId = ShaderCompiler::compile("shaders/Phong.vert", "shaders/Phong.frag");
	blinnPhongShaderId = ShaderCompiler::compile("shaders/BlinnPhong.vert", "shaders/BlinnPhong.frag");
}

Material::Material(MaterialType type) {
	updateType(type);
	baseColor = glm::vec4(0, 0, 0, 1);
	ambientColor = glm::vec4(0, 0, 0, 1);
	diffuseColor = glm::vec4(0, 0, 0, 1);
	specularColor = glm::vec4(0, 0, 0, 1);
	shininess = 1;
}

void Material::bind() {
	glUseProgram(matTypeToId(type));
}

void Material::updateUniforms(Transform t, Camera* c) {
	bind();
	GLuint id = matTypeToId(type);

	glUniformMatrix4fv(glGetUniformLocation(id, "worldMatrix"), 1, GL_FALSE, glm::value_ptr(t.calculateMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(id, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(c->getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(id, "projMatrix"), 1, GL_FALSE, glm::value_ptr(c->getProjMatrix()));
	
	if (type != UNLIT) {
		glUniform4f(glGetUniformLocation(id, "ambientColor"), ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
		glUniform4f(glGetUniformLocation(id, "diffuseColor"), diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		glUniform4f(glGetUniformLocation(id, "specularColor"), specularColor.r, specularColor.g, specularColor.b, specularColor.a);
		glUniform3f(glGetUniformLocation(id, "cameraWorldPos"), c->worldPosition.x, c->worldPosition.y, c->worldPosition.z);
	}
	else {
		glUniform4f(glGetUniformLocation(id, "baseColor"), baseColor.r, baseColor.g, baseColor.b, baseColor.a);
	}
}

void Material::updateType(MaterialType type) {
	this->type = type;
}

GLuint Material::matTypeToId(MaterialType type) {
	switch (type) {
	case Material::UNLIT: 
		return unlitShaderId;
	case Material::GOURAD: 
		return gouradShaderId;
	case Material::PHONG: 
		return phongShaderId;
	case Material::BLINN_PHONG: 
		return blinnPhongShaderId;
	default: 
		return 0;
	}
}

void Material::destroyShaders() {
	glDeleteProgram(unlitShaderId);
	glDeleteProgram(gouradShaderId);
	glDeleteProgram(phongShaderId);
	glDeleteProgram(blinnPhongShaderId);
}