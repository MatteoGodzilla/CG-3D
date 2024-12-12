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
void Object::addChild(Object* child) {
	children.push_back(child);
}

void Object::setTransformSelf(Transform t) {
	transform = t;
	dirtyCollision = true;
}

void Object::setMaterialSelf(Material m) {
	material = m;
}

//force the transform onto the children
void Object::setTransformAll(Transform t) {
	setTransformSelf(t);

	for (auto* child : children) {
		child->setTransformAll(t);
	}
}

void Object::setMaterialAll(Material m) {
	setMaterialSelf(m);

	for (auto* chlid : children) {
		chlid->setMaterialAll(m);
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

std::vector<Object*>& Object::getChildren() {
	return children;
}