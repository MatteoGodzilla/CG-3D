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
	Object(std::string name);
	
	void addChildren(Object* child);
	void setTransformSelf(Transform t);
	void setMaterialSelf(Material m);
	void setTransformAll(Transform t);
	void setMaterialAll(Material m);
	void updateMeshRenderer();
	void updateCollisionBox();
	void render(Camera* c);

	Transform getTransform();
	Mesh* getMesh();
	Material getMaterial();
	CollisionBox getCollision();
	MeshRenderer* getMeshRenderer();

	//functions added just for the hierarchical view
	std::vector<Object*>& getChildren();

	std::string name;
private:
	//this class is owner of the children
	std::vector<Object*> children;
	//this class is owner of this pointer
	Mesh mesh;
	Material material;

	Transform transform;
	MeshRenderer meshRenderer;
	CollisionBox collision;
	bool dirtyCollision;
};