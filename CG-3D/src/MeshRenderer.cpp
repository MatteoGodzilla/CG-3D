#include "MeshRenderer.hpp"

MeshRenderer::MeshRenderer() {
	mesh = nullptr;
	material = nullptr;

	VAO = 0;
	VBO = 0;
	EBO = 0;
}

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : MeshRenderer() {
	this->mesh = mesh;
	this->material = material;
	
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
	//color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(sizeof(glm::vec3) * 2));
	glEnableVertexAttribArray(2);
	//uv
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Mesh::Vertex), (void*)(sizeof(glm::vec3) * 2 + sizeof(glm::vec4)));
	glEnableVertexAttribArray(3);

	//indices
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);
}

void MeshRenderer::updateMaterial(Transform t, Camera* c) {
	if(material != nullptr)
		material->updateUniforms(t, c);
}

void MeshRenderer::render() {
	if (mesh == nullptr || material == nullptr || VAO == 0)
		return;

	material->bind();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
}