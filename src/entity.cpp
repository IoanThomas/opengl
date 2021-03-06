#include "entity.h"

#include <glm/gtc/matrix_transform.hpp>

entity::entity(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: position(position), rotation(rotation), scale(scale)
{
}

glm::mat4 entity::get_transformation_matrix() const
{
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, position);
	transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, scale);

	return transform;
}
