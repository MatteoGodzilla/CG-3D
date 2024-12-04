#include "AssimpConverter.hpp"

#include "Mesh.hpp"
#include "Material.hpp"

Object* createObject(aiNode* node, const aiScene* scene) {
	Mesh* mesh = new Mesh();
	Material* material = new Material();
	//Combine all the meshes found in this node into a single one
	//For the material, use the last one found (because it's easier to code
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
		for (size_t j = 0; j < aiMesh->mNumVertices; j++) {
			Mesh::Vertex v = Mesh::Vertex();
			
			//actually read the data
			v.position = glm::vec3(aiMesh->mVertices[j].x, aiMesh->mVertices[j].y, aiMesh->mVertices[j].z);
			v.normal = glm::vec3(aiMesh->mNormals[j].x, aiMesh->mNormals[j].y, aiMesh->mNormals[j].z);
			v.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
			if (aiMesh->GetNumColorChannels() > 0) {
				v.color = glm::vec4(aiMesh->mColors[j]->r, aiMesh->mColors[j]->g, aiMesh->mColors[j]->b, aiMesh->mColors[j]->a);
			}
			v.uv = glm::vec2(0, 0);
			if (aiMesh->mTextureCoords[0]) {
				v.uv = glm::vec2(aiMesh->mTextureCoords[0][j].x, aiMesh->mTextureCoords[0][j].y);
			}

			//add to our mesh
			mesh->vertices.push_back(v);
		}

		for (size_t j = 0; j < aiMesh->mNumFaces; j++) {
			aiFace aiFace = aiMesh->mFaces[j];
			for (size_t k = 0; k < aiFace.mNumIndices; k++) {
				mesh->indices.push_back(aiFace.mIndices[k]);
			}
		}

		if (aiMesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[aiMesh->mMaterialIndex];
			//load material
		}
	}

	Object* result;
	if (mesh->vertices.size() > 0) {
		result = new Object(mesh, material);
	}
	else {
		result = new Object();
	}
	
	for (size_t i = 0; i < node->mNumChildren; i++) {
		aiNode* child = node->mChildren[i];
		result->addChildren(createObject(child, scene));
	}

	return result;
}

Object* AssimpConverter::loadObject(const char* fileName) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs);
	
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

	return createObject(scene->mRootNode, scene);
}

/*
Mesh* AssimpConverter::aiNodeToMesh(const aiNode* node, const aiScene* scene) {
	Mesh* m = new Mesh();
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

	}

	for (size_t i = 0; i < node->mNumChildren; i++) {
		Mesh* children = aiNodeToMesh(node->mChildren[i], scene);
		m->vertices.insert(m->vertices.end(), children->vertices.begin(), children->vertices.end());
		delete children;
	}

	return m;
	for (size_t i = 0; i < node->mNumMeshes; i++) {
		aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];
		std::cout << "Vertices: " << assimpMesh->mNumVertices << std::endl;
	}

	for (size_t i = 0; i < node->mNumChildren; i++) {
		aiNodeToMesh(node->mChildren[i], scene);
	}

	return nullptr;
}

Material* AssimpConverter::aiNodeToMaterial(const aiNode* node, const aiScene* scene) {
	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* mat = scene->mMaterials[i];
		std::cout << "Material: " << mat->GetName().C_Str() << std::endl;
	}
	
	return nullptr;
}
*/

