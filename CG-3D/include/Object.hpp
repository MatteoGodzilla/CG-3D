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
	
	void addChildren(Object* child);
	void setTransform(Transform t);
	void setMaterial(Material m);
	void updateMeshRenderer();
	void render(Camera* c);

	Transform getTransform();
	Mesh* getMesh();
	Material* getMaterial();

private:
	//this class is owner of the children
	std::vector<Object*> children;
	//this class is owner of this pointer
	Mesh mesh;
	Material material;

	Transform transform;
	MeshRenderer meshRenderer;
	CollisionBox collision;
};