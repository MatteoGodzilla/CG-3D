#pragma once
#include "Mesh.hpp"
#include "Material.hpp"
#include "Transform.hpp"
#include "Camera.hpp"

//contains the references of the opengl VAO, VBO and EBO

class MeshRenderer {
public:
	MeshRenderer();
	MeshRenderer(Mesh* mesh, Material* material);
	void updateMaterial(Transform t, Camera* c);
	void render();

private:
	//this class does NOT own either material nor mesh, they are contained in object
	Material* material;
	Mesh* mesh;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};
