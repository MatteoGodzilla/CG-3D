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

void Material::updateUniforms() {
	switch (type) {
	case UNLIT:
		//glUseProgram(Material::unlitShaderId);
		break;
	case FLAT:
		//glUseProgram(Material::flatShaderId);
		break;
	case GOURAD:
		//glUseProgram(Material::gouradShaderId);
		break;
	case BLINN_PHONG:
		//glUseProgram(Material::blinnPhongShaderId);
		break;
	}
}