#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "model.h"

struct entity
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	entity(const glm::vec3& position, const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));

	glm::mat4 get_transformation_matrix() const;
};
