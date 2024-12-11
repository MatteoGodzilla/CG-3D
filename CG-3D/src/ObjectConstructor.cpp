#include "ObjectConstructor.hpp"

Object* ObjectConstructor::createLightObject(glm::vec3 worldPosition, glm::vec4 color) {
	Object* light = new Object("Light");
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
	light->setTransformAll(lightTransform);

	Material lightMaterial = Material(Material::UNLIT);
	lightMaterial.baseColor = color;
	light->setMaterialAll(lightMaterial);
	return light;
}

Object* ObjectConstructor::createUnitCube() {
	Object* result = new Object("Cube");
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

Object* ObjectConstructor::createRay(glm::vec3 worldPosition, glm::vec3 direction) {
	glm::vec4 gizmoColor = glm::vec4(0,0,0,1);
	float rayLength = 10;
	Object* line = new Object("Ray Line");
	line->getMesh()->vertices.push_back({ {0,0,0} });
	line->getMesh()->vertices.push_back({ rayLength * direction });
	line->getMesh()->indices.push_back(0);
	line->getMesh()->indices.push_back(1);
	line->getMeshRenderer()->renderMode = GL_LINES;
	line->updateMeshRenderer();

	Transform lineTransform = Transform();
	lineTransform.worldPosition = worldPosition;
	line->setTransformAll(lineTransform);

	Material lineMaterial = Material(Material::UNLIT);
	lineMaterial.baseColor = gizmoColor;
	line->setMaterialAll(lineMaterial);
	
	Object* center = createLightObject(worldPosition, gizmoColor);
	center->addChildren(line);
	
	return center;
}