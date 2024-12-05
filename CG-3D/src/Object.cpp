#include "Object.hpp"

Object::Object() {
	children = std::vector<Object*>();
	transform = Transform();
	meshRenderer = MeshRenderer();
	mesh = nullptr;
	material = nullptr;
	collision = CollisionBox();
}

Object::Object(Mesh* mesh, Material* material) {
	children = std::vector<Object*>();
	transform = Transform();
	meshRenderer = MeshRenderer(mesh, material);
	this->mesh = mesh;
	this->material = material;
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

void Object::updateGraphics(Camera* camera) {
	meshRenderer.updateMaterial(transform, camera);

	for (auto* child : children) {
		child->updateGraphics(camera);
	}
}

void Object::render() {
	//first, draw self
	meshRenderer.render();

	//then draw children recursively
	for (auto* child : children) {
		child->render();
	}
}

Object::~Object() {
	if (mesh != nullptr)
		delete mesh;
	if (material != nullptr)
		delete material;
	for (Object* child : children) {
		child->~Object();
		delete child;
	}
}