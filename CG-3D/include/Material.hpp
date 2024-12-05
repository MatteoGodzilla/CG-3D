#pragma once
#include "glad/glad.h"

#include "Utils.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

class Material {
public:
	enum MaterialType {
		UNLIT,
		FLAT,
		GOURAD,
		BLINN_PHONG
	};

	static void initShaders();
	Material(MaterialType type = FLAT);
	void bind();
	void updateUniforms(Transform transform, Camera* camera);
	void updateType(MaterialType type);
	static void destroyShaders();
	
	// various parameters for bling-phong and gourad shading
	glm::vec4 baseColor;
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	float shininess;
	// reference to textures, somehow
private:
	GLuint matTypeToId();
	MaterialType type = UNLIT;
	//need to initialize these somewhere
	static GLuint unlitShaderId;
	static GLuint flatShaderId;
	static GLuint gouradShaderId;
	static GLuint blinnPhongShaderId;

};