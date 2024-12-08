#include "ObjectConstructor.hpp"

Object* ObjectConstructor::createLightObject(glm::vec3 worldPosition, glm::vec4 color) {
	Object* light = new Object();
	//generate light mesh
	auto& lightVertices = light->getMesh()->vertices;
	lightVertices.push_back({ {0, 1, 0} });
	lightVertices.push_back({ {-1, 0, -1} });
	lightVertices.push_back({ {1, 0, 0} });
	lightVertices.push_back({ {-1, 0, 1} });
	lightVertices.push_back({ {0, -1, 0} });
	auto& lightIndices = light->getMesh()->indices;
	lightIndices.push_back(0);
	lightIndices.push_back(2);
	lightIndices.push_back(1);

	lightIndices.push_back(0);
	lightIndices.push_back(2);
	lightIndices.push_back(3);

	lightIndices.push_back(0);
	lightIndices.push_back(1);
	lightIndices.push_back(3);

	lightIndices.push_back(4);
	lightIndices.push_back(1);
	lightIndices.push_back(2);

	lightIndices.push_back(4);
	lightIndices.push_back(3);
	lightIndices.push_back(2);

	lightIndices.push_back(4);
	lightIndices.push_back(3);
	lightIndices.push_back(1);
	light->updateMeshRenderer();

	Transform lightTransform = Transform();
	lightTransform.worldPosition = worldPosition;
	lightTransform.worldScale = glm::vec3(0.1);
	light->setTransform(lightTransform);

	Material lightMaterial = Material();
	lightMaterial.updateType(Material::UNLIT);
	lightMaterial.baseColor = color;
	light->setMaterial(lightMaterial);
	return light;
}