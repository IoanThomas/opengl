#include "point_light.h"

point_light::point_light(const glm::vec3& position, const glm::vec3& colour, const glm::vec3& attenuation)
	: position(position), colour(colour), attenuation(attenuation)
{
}
