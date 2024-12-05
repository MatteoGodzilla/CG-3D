#include "Material.hpp"

//because c++ is a dumb language and these need to be defined somewhere 
GLuint Material::unlitShaderId;
GLuint Material::flatShaderId;
GLuint Material::gouradShaderId;
GLuint Material::blinnPhongShaderId;

void Material::initShaders() {
	unlitShaderId = ShaderCompiler::compile("shaders/Unlit.vert", "shaders/Unlit.frag");
	flatShaderId = ShaderCompiler::compile("shaders/Flat.vert", "shaders/Flat.frag");
	gouradShaderId = ShaderCompiler::compile("shaders/Gourad.vert", "shaders/Gourad.frag");
	blinnPhongShaderId = ShaderCompiler::compile("shaders/BlinnPhong.vert", "shaders/BlinnPhong.frag");
}

void Material::bind() {
	switch (type) {
	case UNLIT:
		glUseProgram(Material::unlitShaderId);
		break;
	case FLAT:
		glUseProgram(Material::flatShaderId);
		break;
	case GOURAD:
		glUseProgram(Material::gouradShaderId);
		break;
	case BLINN_PHONG:
		glUseProgram(Material::blinnPhongShaderId);
		break;
	}
}

void Material::updateUniforms(Transform t, Camera* c) {
	switch (type) {
	case UNLIT:
		glUseProgram(Material::unlitShaderId);
		glUniformMatrix4fv(glGetUniformLocation(Material::unlitShaderId, "worldMatrix"), 1, GL_FALSE, glm::value_ptr(t.calculateMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(Material::unlitShaderId, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(c->getViewMatrix()));
		glUniformMatrix4fv(glGetUniformLocation(Material::unlitShaderId, "projMatrix"), 1, GL_FALSE, glm::value_ptr(c->getProjMatrix()));
		break;
	case FLAT:
		glUseProgram(Material::flatShaderId);
		break;
	case GOURAD:
		glUseProgram(Material::gouradShaderId);
		break;
	case BLINN_PHONG:
		glUseProgram(Material::blinnPhongShaderId);
		break;
	}
}