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

//https://tavianator.com/2011/ray_box.html
bool rayBoxIntersection(CollisionBox box, glm::vec3 rayStart, glm::vec3 rayDirection) {
	auto bounds = box.getBounds();
	bounds.first -= rayStart;
	bounds.second -= rayStart;
	//now bounds can be think of as relative to the origin
	float txMin = bounds.first.x / rayDirection.x;
	float txMax = bounds.second.x / rayDirection.x;
	float tyMin = bounds.first.y / rayDirection.y;
	float tyMax = bounds.second.y / rayDirection.y;
	float tzMin = bounds.first.z / rayDirection.z;
	float tzMax = bounds.second.z / rayDirection.z;

	float tMin = std::max(std::min(txMin, txMax), std::min(tyMin, tyMax));
	tMin = std::max(tMin, std::min(tzMin, tzMax));

	float tMax = std::min(std::max(txMin, txMax), std::max(tyMin, tyMax));
	tMax = std::min(tMax, std::max(tzMin, tzMax));

	return tMax > tMin;
}

Object* CollisionManager::getSelectedObject() {
	auto cameraSelection = camera->getSelectionRay();
	for (auto* object : objects) {
		if (rayBoxIntersection(object->getCollision(), cameraSelection.first, cameraSelection.second))
			return object;
	}
	return nullptr;
}

void CollisionManager::renderCollisions(Camera* cam) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (auto* object : objects) {
		Object* o = ObjectConstructor::createUnitCube();
		auto bounds = object->getCollision().getBounds();
		glm::vec3 scale = (bounds.second - bounds.first) / 2.0f;
		glm::vec3 position = (bounds.first + bounds.second) / 2.0f;

		Transform t = Transform();
		t.worldPosition = position;
		t.worldScale = glm::vec3(scale.x, scale.y, scale.z);
		o->setTransform(t);

		Material m = Material(Material::UNLIT);
		m.baseColor = glm::vec4(1, 1, 1, 1);
		o->setMaterial(m);

		o->render(cam);
		delete o;
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	auto ray = cam->getSelectionRay();
	Object* o = ObjectConstructor::createRay(ray.first, ray.second);
	o->render(cam);
	delete o;
}