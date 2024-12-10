#include "Object.hpp"

Object::Object(std::string name) 
	: mesh(Mesh()), material(Material(Material::UNLIT)), meshRenderer(MeshRenderer(&mesh, &material)) 
{
	children = std::vector<Object*>();
	transform = Transform();
	collision = CollisionBox();
	dirtyCollision = true;
	this->name = name;
}

//now this object is the parent and owner
void Object::addChildren(Object* child) {
	children.push_back(child);
}

//force the transform onto the children
void Object::setTransform(Transform t) {
	transform = t;

	for (auto* child : children) {
		child->setTransform(t);
	}
	dirtyCollision = true;
}

void Object::setMaterial(Material m) {
	material = m;

	for (auto* chlid : children) {
		chlid->setMaterial(m);
	}
}

void Object::render(Camera* camera) {
	material.updateUniforms(transform, camera);
	meshRenderer.render();

	for (auto* child : children) {
		child->render(camera);
	}
}

void Object::updateMeshRenderer() {
	meshRenderer.updateBuffers();

	for (auto* child : children) {
		child->updateMeshRenderer();
	}
}

void Object::updateCollisionBox() {
	if (!dirtyCollision)
		return;
	std::vector<glm::vec3> vertexPoints;

	for (auto* child : children) {
		child->updateCollisionBox();
		auto bounds = child->getCollision().getBounds();
		vertexPoints.push_back(bounds.first);
		vertexPoints.push_back(bounds.second);
	}

	glm::mat4 worldMatrix = transform.calculateMatrix();
	for (auto& vertex : mesh.vertices) {
		glm::vec4 worldPos = worldMatrix * glm::vec4(vertex.position, 1);
		vertexPoints.push_back(glm::vec3(worldPos.x, worldPos.y, worldPos.z));
	}

	collision.updateCollisionBoxFromPoints(vertexPoints);
	dirtyCollision = false;
}

//---GETTERS---
Transform Object::getTransform() {
	return transform;
}

Mesh* Object::getMesh() {
	return &mesh;
}

//returns a copy of the material
Material Object::getMaterial() {
	return material;
}

CollisionBox Object::getCollision() {
	return collision;
}

MeshRenderer* Object::getMeshRenderer() {
	return &meshRenderer;
}