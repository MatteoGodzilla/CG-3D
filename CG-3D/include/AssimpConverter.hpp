#pragma once
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "Object.hpp"

namespace AssimpConverter {
	Object* loadObject(const char* file);
}