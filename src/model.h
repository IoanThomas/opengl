#pragma once

#include "material.h"
#include "opengl/vertex_array.h"

class model
{
public:
	friend class renderer;

	model(gl::vertex_array vao, const material& material);

private:
	gl::vertex_array m_vao;
	material m_material;
};
