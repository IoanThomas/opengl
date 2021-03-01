#pragma once

#include <memory>

#include "opengl/texture.h"

class material
{
public:
	material(const std::shared_ptr<gl::texture> diffuse, const std::shared_ptr<gl::texture> detail, const float shininess);

	const gl::texture& get_diffuse_texture() const { return *m_diffuse; }
	const gl::texture& get_detail_texture() const { return *m_detail; }
	float get_shininess() const { return m_shininess; }

private:
	std::shared_ptr<gl::texture> m_diffuse;
	std::shared_ptr<gl::texture> m_detail;
	float m_shininess;
};
