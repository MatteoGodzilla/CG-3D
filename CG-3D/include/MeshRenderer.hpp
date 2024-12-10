#pragma once
#include "Mesh.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

//contains the references of the opengl VAO, VBO and EBO

class MeshRenderer {
public:
	MeshRenderer(Mesh* mesh, Material* material);
	void updateBuffers();
	void render();

	GLint renderMode;
private:
	//this class does NOT own either material nor mesh, they are contained in object
	Material* material;
	Mesh* mesh;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};
