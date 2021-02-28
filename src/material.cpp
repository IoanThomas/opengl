#include "material.h"

material::material(const std::shared_ptr<gl::texture> diffuse, const std::shared_ptr<gl::texture> detail, const float shininess)
	: m_diffuse(diffuse), m_detail(detail), m_shininess(shininess)
{
}
