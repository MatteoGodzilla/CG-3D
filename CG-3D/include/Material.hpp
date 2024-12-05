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
	void bind();
	void updateUniforms(Transform transform, Camera* camera);
	void updateType(MaterialType type);
private:
	// various parameters for bling-phong and gourad shading
	// reference to textures, somehow

	MaterialType type = UNLIT;
	//need to initialize these somewhere
	static GLuint unlitShaderId;
	static GLuint flatShaderId;
	static GLuint gouradShaderId;
	static GLuint blinnPhongShaderId;

};