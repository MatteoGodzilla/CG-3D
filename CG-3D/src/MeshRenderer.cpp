#include "MeshRenderer.hpp"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) {
	this->mesh = mesh;
	this->material = material;
	VAO = 0;
	VBO = 0;
	EBO = 0;

	//upload to opengl
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//vertex data
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Mesh::Vertex), mesh->vertices.data(), GL_DYNAMIC_DRAW);
	
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(sizeof(glm::vec3)));
	glEnableVertexAttribArray(1);
	//uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(sizeof(glm::vec3) * 2));
	glEnableVertexAttribArray(2);

	//indices
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);
	renderMode = GL_TRIANGLES;
}

void MeshRenderer::updateBuffers() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Mesh::Vertex), mesh->vertices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);
}

void MeshRenderer::render() {
	if (mesh->indices.size() == 0)
		return;

	material->bind();
	if (material->type == Material::UNLIT_WIREFRAME) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glBindVertexArray(VAO);
	glDrawElements(renderMode, mesh->indices.size(), GL_UNSIGNED_INT, 0);
}