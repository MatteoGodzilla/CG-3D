#pragma once
#include <vector>
#include "glad/glad.h"
#include "Object.hpp"
#include "Camera.hpp"
#include "ObjectConstructor.hpp"

//this class assumes that the objects are static in the scene, 
//so we just have to check against the camera that's moving
//collision type is just sphere <--> AABB
class CollisionManager {
public:
	CollisionManager(Camera* camera);
	void addObject(Object* object);
	void updateCollisions();
	void resolveCollisions();
	void renderCollisions(Camera* cam);

	Object* getSelectedObject();
private:
	std::vector<Object*> objects;
	Camera* camera;
};