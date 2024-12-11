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
		UNLIT_TEXTURE,
		UNLIT_CUBEMAP,
		GOURAD,
		PHONG,
		BLINN_PHONG,
		MAT_TYPE_COUNT // just to make loops easier 
	};

	static void initShaders();
	Material(MaterialType type);
	void bind();
	void updateUniforms(Transform transform, Camera* camera);
	static void destroyShaders();
	static GLuint matTypeToId(MaterialType type);

	MaterialType type;
	// various parameters for bling-phong and gourad shading
	glm::vec4 baseColor;
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float shininess;
	// reference to textures
	// UNLIT_TEXTURE -> texture != nullptr; UNLIT_CUBEMAP -> cubemap != nullptr; everything else has both nullptr;
	Texture* texture;
	Cubemap* cubemap;
private:

	//need to initialize these somewhere
	static GLuint unlitShaderId;
	static GLuint gouradShaderId;
	static GLuint phongShaderId;
	static GLuint blinnPhongShaderId;
	static GLuint unlitTextureShaderId;
	static GLuint unlitCubemapShaderId;

};