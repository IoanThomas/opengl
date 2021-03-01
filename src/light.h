#pragma once

#include <glm/glm.hpp>

struct light
{
public:
	glm::vec3 position;
	glm::vec3 colour;
	glm::vec3 attenuation;

	light(const glm::vec3& position, const glm::vec3& colour = glm::vec3(1.0f), const glm::vec3& attenuation = glm::vec3(1.0f, 0.0f, 0.0f));
};
