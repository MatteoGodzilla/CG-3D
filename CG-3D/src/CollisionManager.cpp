#include "CollisionManager.hpp"

CollisionManager::CollisionManager(Camera* camera) {
	this->camera = camera;
	objects = std::vector<Object*>();
}

void CollisionManager::addObject(Object* object) {
	objects.push_back(object);
}

void CollisionManager::updateCollisions() {
	for (auto* object : objects) {
		object->updateCollisionBox();
	}
}

//actual physics calculation
void CollisionManager::resolveCollisions() {
	auto cameraBounds = camera->getCollision().getBounds();
	for (auto* object : objects) {
		CollisionBox collision = object->getCollision();
		glm::vec3 closestPoint = collision.clampPointToBounds(cameraBounds.first);
		if (camera->getCollision().isPointInsideCollisionSphere(closestPoint)) {
			glm::vec3 resolutionVector = glm::normalize(cameraBounds.first- closestPoint);
			float collisionDistance = glm::length(closestPoint - cameraBounds.first);
			cameraBounds.first += resolutionVector * (cameraBounds.second - collisionDistance);
		}
	}
	camera->worldPosition = cameraBounds.first;
}