#pragma once
#include <vector>
#include "glm/glm.hpp"

//Should only contain the data for the model, completely agnostic of the graphic rendering
struct Mesh {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec4 color;
		glm::vec2 uv;
	};
	std::vector<Vertex> vertices = std::vector<Vertex>();
	std::vector<unsigned int> indices = std::vector<unsigned int>();
};