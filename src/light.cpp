#include "light.h"

light::light(const glm::vec3& position, const glm::vec3& colour, const glm::vec3& attenuation)
	: position(position), colour(colour), attenuation(attenuation)
{
}
