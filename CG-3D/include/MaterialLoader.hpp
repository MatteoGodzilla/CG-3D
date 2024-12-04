#pragma once
#include "Material.hpp"

namespace MaterialLoader {
	//creates a 'new' material object and gives ownership to the callee
	Material* loadMaterial(const char* fileName, Material::MaterialType type);
}