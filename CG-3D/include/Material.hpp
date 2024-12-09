#pragma once
#include "glad/glad.h"

#include "Utils.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

class Material {
public:
	enum MaterialType {
		UNLIT,
		GOURAD,
		PHONG,
		BLINN_PHONG,
		UNLIT_TEXTURE,
		UNLIT_CUBEMAP,
	};

	static void initShaders();
	Material(MaterialType type);
	void bind();
	void updateUniforms(Transform transform, Camera* camera);
	void updateType(MaterialType type);
	static void destroyShaders();
	static GLuint matTypeToId(MaterialType type);
	
	// various parameters for bling-phong and gourad shading
	glm::vec4 baseColor;
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float shininess;
	// reference to textures
	// these can either be: both nullptr or one of each nullptr, NOT both
	Texture* texture;
	Cubemap* cubemap;
private:
	MaterialType type;

	//need to initialize these somewhere
	static GLuint unlitShaderId;
	static GLuint gouradShaderId;
	static GLuint phongShaderId;
	static GLuint blinnPhongShaderId;
	static GLuint unlitTextureShaderId;
	static GLuint unlitCubemapShaderId;

};