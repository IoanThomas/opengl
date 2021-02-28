#pragma once

#include "material.h"
#include "opengl/vertex_array.h"

class model
{
public:
	model(gl::vertex_array vao, const material& material);

	gl::vertex_array& get_vao() { return m_vao; }
	material& get_material() { return m_material; }

private:
	gl::vertex_array m_vao;
	material m_material;
};
