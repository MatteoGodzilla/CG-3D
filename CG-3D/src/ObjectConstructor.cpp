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

	Material lightMaterial = Material(Material::UNLIT);
	lightMaterial.baseColor = color;
	light->setMaterial(lightMaterial);
	return light;
}

Object* ObjectConstructor::createSkybox() {
	Object* result = new Object();
	auto& vertices = result->getMesh()->vertices;
	vertices.push_back({ {-1, -1, -1} }); //left	bottom	back
	vertices.push_back({ {+1, -1, -1} }); //right	bottom	back
	vertices.push_back({ {-1, +1, -1} }); //left	top		back
	vertices.push_back({ {+1, +1, -1} }); //right	top		back
	vertices.push_back({ {-1, -1, +1} }); //left	bottom	front
	vertices.push_back({ {+1, -1, +1} }); //right	bottom	front
	vertices.push_back({ {-1, +1, +1} }); //left	top		front
	vertices.push_back({ {+1, +1, +1} }); //right	top		front

	auto& indices = result->getMesh()->indices;
	//front face
	indices.push_back(6);
	indices.push_back(4);
	indices.push_back(7);

	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(4);
	//right face
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(3);
	
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(5);
	
	//back face
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	//left face
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(6);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(0);
	//up face
	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(3);

	indices.push_back(7);
	indices.push_back(3);
	indices.push_back(6);
	//down face
	indices.push_back(4);
	indices.push_back(0);
	indices.push_back(5);

	indices.push_back(5);
	indices.push_back(0);
	indices.push_back(1);

	result->updateMeshRenderer();
	return result;
}