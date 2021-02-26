#include "model.h"

#include <utility>

model::model(gl::vertex_array vao, const material& material)
	: m_vao(std::move(vao)), m_material(material)
{
}
