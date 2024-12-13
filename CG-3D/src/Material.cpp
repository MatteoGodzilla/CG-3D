#include "Material.hpp"

//because c++ is a dumb language and these need to be defined somewhere 
GLuint Material::unlitShaderId;
GLuint Material::unlitTextureShaderId;
GLuint Material::unlitCubemapShaderId;
GLuint Material::gouradShaderId;
GLuint Material::phongShaderId;
GLuint Material::blinnPhongShaderId;

void Material::initShaders() {
	unlitShaderId = ShaderCompiler::compile("shaders/Unlit.vert", "shaders/Unlit.frag");
	unlitTextureShaderId = ShaderCompiler::compile("shaders/UnlitTexture.vert", "shaders/UnlitTexture.frag");
	unlitCubemapShaderId = ShaderCompiler::compile("shaders/Skybox.vert", "shaders/Skybox.frag");
	gouradShaderId = ShaderCompiler::compile("shaders/Gourad.vert", "shaders/Gourad.frag");
	phongShaderId = ShaderCompiler::compile("shaders/Phong.vert", "shaders/Phong.frag");
	blinnPhongShaderId = ShaderCompiler::compile("shaders/BlinnPhong.vert", "shaders/BlinnPhong.frag");
}

Material::Material(MaterialType type) {
	this->type = type;
	baseColor = glm::vec4(0, 0, 0, 1);
	ambientColor = glm::vec4(0, 0, 0, 1);
	diffuseColor = glm::vec4(0, 0, 0, 1);
	specularColor = glm::vec4(0, 0, 0, 1);
	shininess = 100;
	reflectivity = 0.5;
	texture = nullptr;
	cubemap = nullptr;
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

	switch (type) {
	case UNLIT_CUBEMAP:
		if (cubemap != nullptr) glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->cubemapId);
		glUniform4f(glGetUniformLocation(id, "baseColor"), baseColor.r, baseColor.g, baseColor.b, baseColor.a);
		break;
	case UNLIT_TEXTURE:
		if(texture != nullptr) glBindTexture(GL_TEXTURE_2D, texture->texId);
		glUniform4f(glGetUniformLocation(id, "baseColor"), baseColor.r, baseColor.g, baseColor.b, baseColor.a);
		break;
	case UNLIT:
	case UNLIT_WIREFRAME:
		glUniform4f(glGetUniformLocation(id, "baseColor"), baseColor.r, baseColor.g, baseColor.b, baseColor.a);
		break;
	case GOURAD:
	case PHONG:
	case BLINN_PHONG:
		if (cubemap != nullptr) glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->cubemapId);
		glUniform4f(glGetUniformLocation(id, "ambientColor"), ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
		glUniform4f(glGetUniformLocation(id, "diffuseColor"), diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		glUniform4f(glGetUniformLocation(id, "specularColor"), specularColor.r, specularColor.g, specularColor.b, specularColor.a);
		glUniform1i(glGetUniformLocation(id, "shininess"), shininess);
		glUniform1f(glGetUniformLocation(id, "reflectivity"), reflectivity);
		glUniform3f(glGetUniformLocation(id, "cameraWorldPos"), c->worldPosition.x, c->worldPosition.y, c->worldPosition.z);
		break;
	}
}

GLuint Material::matTypeToId(MaterialType type) {
	switch (type) {
	case Material::UNLIT:
	case Material::UNLIT_WIREFRAME:
		return unlitShaderId;
	case Material::GOURAD: 
		return gouradShaderId;
	case Material::PHONG: 
		return phongShaderId;
	case Material::BLINN_PHONG: 
		return blinnPhongShaderId;
	case Material::UNLIT_TEXTURE:
		return unlitTextureShaderId;
	case Material::UNLIT_CUBEMAP:
		return unlitCubemapShaderId;
	default: 
		std::cerr << "[Material] Invalid type set: " << type << std::endl;
		exit(Error::MATERIAL_TYPE_INVALID);
		return 0;
	}
}

void Material::destroyShaders() {
	glDeleteProgram(unlitShaderId);
	glDeleteProgram(unlitTextureShaderId);
	glDeleteProgram(unlitCubemapShaderId);
	glDeleteProgram(gouradShaderId);
	glDeleteProgram(phongShaderId);
	glDeleteProgram(blinnPhongShaderId);
}