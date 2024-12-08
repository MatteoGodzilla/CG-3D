#pragma once
#include <vector>
#include "Object.hpp"
#include "Camera.hpp"

//this class assumes that the objects are static in the scene, 
//so we just have to check against the camera that's moving
//collision type is just sphere <--> AABB
class CollisionManager {
public:
	CollisionManager(Camera* camera);
	void addObject(Object* object);
	void updateCollisions();
	void resolveCollisions();
private:
	std::vector<Object*> objects;
	Camera* camera;
};