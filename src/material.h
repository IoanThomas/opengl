#pragma once

#include <memory>

#include "opengl/texture.h"

class material
{
public:
	material(const std::shared_ptr<gl::texture> diffuse, const std::shared_ptr<gl::texture> detail, const float shininess);

public:
	std::shared_ptr<gl::texture> m_diffuse;
	std::shared_ptr<gl::texture> m_detail;
	//std::shared_ptr<gl::texture> m_emission;
	float m_shininess;
};
