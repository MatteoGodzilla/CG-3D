#include "Object.hpp"

Object::Object() 
	: mesh(Mesh()), material(Material()), meshRenderer(MeshRenderer(&mesh, &material)) 
{
	children = std::vector<Object*>();
	transform = Transform();
	collision = CollisionBox();
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