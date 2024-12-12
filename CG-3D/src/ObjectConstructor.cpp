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

//divide into each face as a separate object
Object* ObjectConstructor::createUnitCube() {
	Object* result = new Object("Cube");
	auto& vertices = result->getMesh()->vertices;
	
	//yes, i do realise that this is awful, but it kinda has a bit of sense
	glm::vec3 LBB = { -1, -1, -1 };	//left	bottom	back
	glm::vec3 RBB = { +1, -1, -1 };	//right	bottom	back
	glm::vec3 LTB = { -1, +1, -1 };	//left	top		back
	glm::vec3 RTB = { +1, +1, -1 };	//right	top		back
	glm::vec3 LBF = { -1, -1, +1 };	//left	bottom	front
	glm::vec3 RBF = { +1, -1, +1 };	//right	bottom	front
	glm::vec3 LTF = { -1, +1, +1 };	//left	top		front
	glm::vec3 RTF = { +1, +1, +1 };	//right	top		front

	//front face
	Object* frontFace = new Object("frontFace");
	glm::vec3 frontNormal = { 0, 0, 1 };
	auto& frontVertices = frontFace->getMesh()->vertices;
	frontVertices.push_back({ RTF, frontNormal});
	frontVertices.push_back({ LTF, frontNormal});
	frontVertices.push_back({ LBF, frontNormal});
	frontVertices.push_back({ RBF, frontNormal});
	auto& frontIndices = frontFace->getMesh()->indices;
	frontIndices.push_back(0);
	frontIndices.push_back(1);
	frontIndices.push_back(2);
	frontIndices.push_back(2);
	frontIndices.push_back(3);
	frontIndices.push_back(0);
	frontFace->updateMeshRenderer();
	result->addChild(frontFace);

	//right face
	Object* rightFace = new Object("rightFace");
	glm::vec3 rightNormal = { 1, 0, 0 };
	auto& rightVertices = rightFace->getMesh()->vertices;
	rightVertices.push_back({ RTB, rightNormal });
	rightVertices.push_back({ RTF, rightNormal });
	rightVertices.push_back({ RBF, rightNormal });
	rightVertices.push_back({ RBB, rightNormal });
	auto& rightIndices = rightFace->getMesh()->indices;
	rightIndices.push_back(0);
	rightIndices.push_back(1);
	rightIndices.push_back(2);
	rightIndices.push_back(2);
	rightIndices.push_back(3);
	rightIndices.push_back(0);
	rightFace->updateMeshRenderer();
	result->addChild(rightFace);

	//back face
	Object* backFace = new Object("backFace");
	glm::vec3 backNormal = { 0, 0, -1 };
	auto& backVertices = backFace->getMesh()->vertices;
	backVertices.push_back({ LTB, backNormal });
	backVertices.push_back({ RTB, backNormal });
	backVertices.push_back({ RBB, backNormal });
	backVertices.push_back({ LBB, backNormal });
	auto& backIndices = backFace->getMesh()->indices;
	backIndices.push_back(0);
	backIndices.push_back(1);
	backIndices.push_back(2);
	backIndices.push_back(2);
	backIndices.push_back(3);
	backIndices.push_back(0);
	backFace->updateMeshRenderer();
	result->addChild(backFace);

	//left face
	Object * leftFace = new Object("leftFace");
	glm::vec3 leftNormal = { -1, 0, 0 };
	auto& leftVertices = leftFace->getMesh()->vertices;
	leftVertices.push_back({ LTF, leftNormal });
	leftVertices.push_back({ LTB, leftNormal });
	leftVertices.push_back({ LBB, leftNormal });
	leftVertices.push_back({ LBF, leftNormal });
	auto& leftIndices = leftFace->getMesh()->indices;
	leftIndices.push_back(0);
	leftIndices.push_back(1);
	leftIndices.push_back(2);
	leftIndices.push_back(2);
	leftIndices.push_back(3);
	leftIndices.push_back(0);
	leftFace->updateMeshRenderer();
	result->addChild(leftFace);

	//top face
	Object * topFace = new Object("topFace");
	glm::vec3 topNormal = { 0, 1, 0 };
	auto& topVertices = topFace->getMesh()->vertices;
	topVertices.push_back({ RTB, topNormal });
	topVertices.push_back({ LTB, topNormal });
	topVertices.push_back({ LTF, topNormal });
	topVertices.push_back({ RTF, topNormal });
	auto& topIndices = topFace->getMesh()->indices;
	topIndices.push_back(0);
	topIndices.push_back(1);
	topIndices.push_back(2);
	topIndices.push_back(2);
	topIndices.push_back(3);
	topIndices.push_back(0);
	topFace->updateMeshRenderer();
	result->addChild(topFace);

	//bottom face
	Object * bottomFace = new Object("bottomFace");
	glm::vec3 bottomNormal = { 0, -1, 0 };
	auto& bottomVertices = bottomFace->getMesh()->vertices;
	bottomVertices.push_back({ RBF, bottomNormal });
	bottomVertices.push_back({ LBF, bottomNormal });
	bottomVertices.push_back({ LBB, bottomNormal });
	bottomVertices.push_back({ RBB, bottomNormal });
	auto& bottomIndices = bottomFace->getMesh()->indices;
	bottomIndices.push_back(0);
	bottomIndices.push_back(1);
	bottomIndices.push_back(2);
	bottomIndices.push_back(2);
	bottomIndices.push_back(3);
	bottomIndices.push_back(0);
	bottomFace->updateMeshRenderer();
	result->addChild(bottomFace);

	result->updateCollisionBox();
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
	center->addChild(line);
	
	return center;
}

//divide into sides and base as separate objects
Object* ObjectConstructor::createUnitPyramid() {
	Object* pyramid = ObjectConstructor::createUnitCone(4);
	Transform t = Transform();
	t.worldRotation = glm::rotate(t.worldRotation, glm::quarter_pi<float>(), glm::vec3(0, 1, 0));
	pyramid->setTransformAll(t);
	return pyramid;
	/*
	Object* result = new Object("Pyramid");
	auto& vertices = result->getMesh()->vertices;
	vertices.push_back({ {-0.5,0,0.5} });
	vertices.push_back({ {0.5,0,0.5} });
	vertices.push_back({ {0.5,0,-0.5} });
	vertices.push_back({ {-0.5,0,-0.5} });
	vertices.push_back({ {0,1,0} });

	auto& indices = result->getMesh()->indices;
	//bottom face
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	//side faces

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(4);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(0);
	indices.push_back(4);

	result->updateMeshRenderer();
	result->updateCollisionBox();

	Material m = Material(Material::UNLIT);
	m.baseColor = glm::vec4(1, 1, 1, 1);
	result->setMaterialSelf(m);

	return result;
	*/
}

Object* ObjectConstructor::createUnitSphere(int latResolution, int lonResolution) {
	Object* result = new Object("Sphere");

	auto& vertices = result->getMesh()->vertices;

	for (int i = 0; i <= latResolution; i++) {
		for (int j = 0; j < lonResolution; j++) {
			float lat = glm::half_pi<float>() - ((float)i / latResolution) * glm::pi<float>();
			float lon = ((float)j / lonResolution) * glm::two_pi<float>();

			glm::vec3 point = glm::vec3(cos(lat) * sin(lon), sin(lat), cos(lat) * cos(lon));
			
			vertices.push_back({ point, point });
		}
	}

	auto& indices = result->getMesh()->indices;

	for (int i = 0; i < latResolution; i++) {
		for (int j = 0; j < lonResolution; j++) {
			int TLindex = i * lonResolution + j;
			int TRindex = i * lonResolution + (j + 1) % lonResolution;
			int BLindex = (i+1) * lonResolution + j;
			int BRindex = (i+1) * lonResolution + (j + 1) % lonResolution;

			indices.push_back(TLindex);
			indices.push_back(BRindex);
			indices.push_back(TRindex);

			indices.push_back(BRindex);
			indices.push_back(TLindex);
			indices.push_back(BLindex);
		}
	}

	result->updateMeshRenderer();
	result->updateCollisionBox();

	Material m = Material(Material::UNLIT);
	m.baseColor = glm::vec4(1, 1, 1, 1);
	result->setMaterialSelf(m);
	return result;
}

Object* ObjectConstructor::createUnitCylinder(int circleResolution) {
	Object* result = new Object("Cylinder");

	//create top face
	Object* top = new Object("Cylinder Top");
	auto& topVertices = top->getMesh()->vertices;

	topVertices.push_back({ {0,0.5,0}, {0,1,0} });

	for (int j = 0; j < circleResolution; j++) {
		float lon = ((float)j / circleResolution) * glm::two_pi<float>();
		glm::vec3 top = glm::vec3(sin(lon) / 2, 0.5, cos(lon) / 2);
		topVertices.push_back({ top, {0,0.5,0} });
	}

	auto& topIndices = top->getMesh()->indices;
	for (int i = 0; i < topVertices.size(); i++)
		topIndices.push_back(i);
	topIndices.push_back(1);

	Material topMaterial = Material(Material::UNLIT);
	topMaterial.baseColor = glm::vec4(1, 0, 0, 1);
	top->setMaterialSelf(topMaterial);

	top->updateMeshRenderer();
	top->getMeshRenderer()->renderMode = GL_TRIANGLE_FAN;
	result->addChild(top);

	//create label face
	Object* label = new Object("Cylinder Label");
	auto& labelVertices = label->getMesh()->vertices;

	for (int j = 0; j < circleResolution; j++) {
		float lon = ((float)j / circleResolution) * glm::two_pi<float>();
		glm::vec3 top = glm::vec3(sin(lon) / 2, 0.5, cos(lon) / 2);
		glm::vec3 bottom = glm::vec3(sin(lon) / 2, -0.5, cos(lon) / 2);

		glm::vec3 normal = glm::vec3(sin(lon), 0, cos(lon));

		labelVertices.push_back({ top, normal });
		labelVertices.push_back({ bottom, normal });
	}

	auto& labelIndices = label->getMesh()->indices;
	for (int j = 0; j < circleResolution; j++) {
		int TLindex = 2 * j + 0;
		int BLindex = 2 * j + 1;
		int TRindex = 2 * ((j + 1) % circleResolution) + 0;
		int BRindex = 2 * ((j + 1) % circleResolution) + 1;

		labelIndices.push_back(TLindex);
		labelIndices.push_back(BLindex);
		labelIndices.push_back(TRindex);

		labelIndices.push_back(TRindex);
		labelIndices.push_back(BLindex);
		labelIndices.push_back(BRindex);
	}

	label->updateMeshRenderer();
	Material labelMaterial = Material(Material::UNLIT);
	labelMaterial.baseColor = glm::vec4(1, 1, 1, 1);
	label->setMaterialSelf(labelMaterial);

	result->addChild(label);

	//create bottom face
	Object* bottom = new Object("Cylinder Bottom");
	auto& bottomVertices = bottom->getMesh()->vertices;

	bottomVertices.push_back({ {0,-0.5,0}, {0,-1,0} });

	for (int j = 0; j < circleResolution; j++) {
		float lon = ((float)j / circleResolution) * glm::two_pi<float>();
		glm::vec3 top = glm::vec3(sin(lon) / 2, -0.5, cos(lon) / 2);
		bottomVertices.push_back({ top, {0,-1,0} });
	}

	auto& bottomIndices = bottom->getMesh()->indices;
	for (int i = 0; i < bottomVertices.size(); i++)
		bottomIndices.push_back(i);
	bottomIndices.push_back(1);

	Material bottomMaterial = Material(Material::UNLIT);
	bottomMaterial.baseColor = glm::vec4(0, 0, 1, 1);
	bottom->setMaterialSelf(bottomMaterial);

	bottom->updateMeshRenderer();
	bottom->getMeshRenderer()->renderMode = GL_TRIANGLE_FAN;
	result->addChild(bottom);

	return result;
}

Object* ObjectConstructor::createUnitCone(int circleResolution) {
	Object* result = new Object("Cone");
	
	//add side
	//create top face
	Object* side = new Object("Cone Side");
	auto& sideVertices = side->getMesh()->vertices;

	sideVertices.push_back({ {0,1,0}, {0,1,0} });

	for (int j = 0; j < circleResolution; j++) {
		float lon = ((float)j / circleResolution) * glm::two_pi<float>();
		glm::vec3 position = glm::vec3(sin(lon) / 2, 0, cos(lon) / 2);
		glm::vec3 normal = { sin(lon), 0, cos(lon)};
		sideVertices.push_back({ position, normal });
	}

	auto& sideIndices = side->getMesh()->indices;
	for (int i = 0; i < sideVertices.size(); i++)
		sideIndices.push_back(i);
	sideIndices.push_back(1);

	Material sideMaterial = Material(Material::UNLIT);
	sideMaterial.baseColor = glm::vec4(1, 0, 0, 1);
	side->setMaterialSelf(sideMaterial);

	side->updateMeshRenderer();
	side->getMeshRenderer()->renderMode = GL_TRIANGLE_FAN;
	result->addChild(side);

	//add bottom face
	Object* bottom = new Object("Cone Bottom");
	auto& bottomVertices = bottom->getMesh()->vertices;

	bottomVertices.push_back({ {0,0,0}, {0,-1,0} });

	for (int j = 0; j < circleResolution; j++) {
		float lon = ((float)j / circleResolution) * glm::two_pi<float>();
		glm::vec3 top = glm::vec3(sin(lon) / 2, 0, cos(lon) / 2);
		bottomVertices.push_back({ top, {0,-1,0} });
	}

	auto& bottomIndices = bottom->getMesh()->indices;
	for (int i = 0; i < bottomVertices.size(); i++)
		bottomIndices.push_back(i);
	bottomIndices.push_back(1);

	Material bottomMaterial = Material(Material::UNLIT);
	bottomMaterial.baseColor = glm::vec4(0, 0, 1, 1);
	bottom->setMaterialSelf(bottomMaterial);

	bottom->updateMeshRenderer();
	bottom->getMeshRenderer()->renderMode = GL_TRIANGLE_FAN;

	result->addChild(bottom);
	return result;
}

Object* ObjectConstructor::createTorus(float outerRadius, float sliceRadius, int outerResolution, int sliceResolution) {
	Object* result = new Object("Torus");

	auto& vertices = result->getMesh()->vertices;

	for (int i = 0; i < outerResolution; i++) {
		float outerAngle = ((float)i / outerResolution) * glm::two_pi<float>();
		glm::vec3 outsideVector = glm::vec3(cos(outerAngle), 0, sin(outerAngle));
		glm::vec3 sliceCenter = outerRadius * outsideVector;
		glm::vec3 upVector = glm::vec3(0, 1, 0);

		for (int j = 0; j < sliceResolution; j++) {
			float sliceAngle = ((float)j / sliceResolution) * glm::two_pi<float>();
			//might need normalize
			glm::vec3 pointNormal = outsideVector * cos(sliceAngle) + upVector * sin(sliceAngle);
			glm::vec3 point = sliceCenter + sliceRadius * pointNormal;
			vertices.push_back({ point, pointNormal });
		}
	}

	auto& indices = result->getMesh()->indices;

	for (int i = 0; i < outerResolution; i++) {
		for (int j = 0; j < sliceResolution; j++) {
			int TLindex = i * sliceResolution + j;
			int TRindex = i * sliceResolution + (j + 1) % sliceResolution;
			int BLindex = ((i + 1) % outerResolution) * sliceResolution + j;
			int BRindex = ((i + 1) % outerResolution) * sliceResolution + (j + 1) % sliceResolution;

			indices.push_back(TLindex);
			indices.push_back(BRindex);
			indices.push_back(TRindex);

			indices.push_back(BRindex);
			indices.push_back(TLindex);
			indices.push_back(BLindex);
		}
	}

	result->updateMeshRenderer();
	result->updateCollisionBox();

	Material m = Material(Material::UNLIT);
	m.baseColor = glm::vec4(1, 1, 1, 1);
	result->setMaterialAll(m);

	return result;
}