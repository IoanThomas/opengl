#include "material.h"

material::material(const std::shared_ptr<gl::texture> diffuse, const std::shared_ptr<gl::texture> specular, const float shininess)
	: m_diffuse(diffuse), m_specular(specular), m_shininess(shininess)
{
}
