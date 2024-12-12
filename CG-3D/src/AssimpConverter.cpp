#include "AssimpConverter.hpp"

Object* createObject(aiNode* node, const aiScene* scene) {
	Object* result = new Object(node->mName.C_Str());
	
	//Combine all the meshes found in this node into a single one
	//For the material, use the last one found (because it's easier to code
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
		for (size_t j = 0; j < aiMesh->mNumVertices; j++) {
			Mesh::Vertex v = Mesh::Vertex();
			
			//actually read the data
			v.position = glm::vec3(aiMesh->mVertices[j].x, aiMesh->mVertices[j].y, aiMesh->mVertices[j].z);
			v.normal = glm::vec3(aiMesh->mNormals[j].x, aiMesh->mNormals[j].y, aiMesh->mNormals[j].z);
			v.uv = glm::vec2(0, 0);
			if (aiMesh->mTextureCoords[0]) {
				v.uv = glm::vec2(aiMesh->mTextureCoords[0][j].x, aiMesh->mTextureCoords[0][j].y);
			}

			//add to our mesh
			result->getMesh()->vertices.push_back(v);
		}

		for (size_t j = 0; j < aiMesh->mNumFaces; j++) {
			aiFace aiFace = aiMesh->mFaces[j];
			for (size_t k = 0; k < aiFace.mNumIndices; k++) {
				result->getMesh()->indices.push_back(aiFace.mIndices[k]);
			}
		}

		if (aiMesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[aiMesh->mMaterialIndex];
			Material myMat = Material(Material::BLINN_PHONG);
			//load material
			aiColor4D baseColor;
			aiColor4D ambientColor;
			aiColor4D diffuseColor;
			aiColor4D specularColor;
			float shininess;
			if (mat->Get(AI_MATKEY_BASE_COLOR, baseColor) == aiReturn_SUCCESS) {
				myMat.baseColor = glm::vec4(baseColor.r, baseColor.g, baseColor.b, baseColor.a);
			}
			if (mat->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == aiReturn_SUCCESS) {
				myMat.ambientColor = glm::vec4(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
			}
			if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == aiReturn_SUCCESS) {
				myMat.diffuseColor = glm::vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
			}
			if (mat->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == aiReturn_SUCCESS) {
				myMat.specularColor = glm::vec4(specularColor.r, specularColor.g, specularColor.b, specularColor.a);
			}
			if (mat->Get(AI_MATKEY_SHININESS, shininess) == aiReturn_SUCCESS) {
				myMat.shininess = shininess;
			}
			result->setMaterialAll(myMat);
		}
	}
	
	for (size_t i = 0; i < node->mNumChildren; i++) {
		aiNode* child = node->mChildren[i];
		result->addChild(createObject(child, scene));
	}

	return result;
}

Object* AssimpConverter::loadObject(const char* fileName) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	
	if (scene == nullptr) {
		std::cerr << "[AssimpConverter] Scene is null: " << importer.GetErrorString() << std::endl;
		exit(Error::ASSIMP_SCENE_IS_NULL);
	}

	if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		std::cerr << "[AssimpConverter] Scene is incomplete: " << importer.GetErrorString() << std::endl;
		exit(Error::ASSIMP_SCENE_IS_INCOMPLETE);
	}

	if (scene->mRootNode == nullptr) {
		std::cerr << "[AssimpConverter] Root node is null: " << importer.GetErrorString() << std::endl;
		exit(Error::ASSIMP_ROOT_IS_NULL);
	}

	Object* result = createObject(scene->mRootNode, scene);
	importer.FreeScene();
	result->updateMeshRenderer();
	return result;
}

