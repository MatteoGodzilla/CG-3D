#pragma once
#include <vector>
#include "Transform.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "CollisionBox.hpp"
#include "Camera.hpp"

//This object is meant to be created dynamically with 'new'
class Object {
public:
	Object();
	Object(Mesh* mesh, Material* material);
	
	void addChildren(Object* child);
	void setTransform(Transform t);
	void updateGraphics(Camera* c);
	void render();

	~Object();

	Transform transform;
private:
	//this class is owner of the children
	std::vector<Object*> children;
	//this class is owner of this pointer
	Mesh* mesh;
	Material* material;

	MeshRenderer meshRenderer;
	CollisionBox collision;
};