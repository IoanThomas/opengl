#include "vertex_array.h"

#include <cstddef>

gl::vertex_array::vertex_array(const std::shared_ptr<element_buffer> ebo, const std::shared_ptr<vertex_buffer> vbo, const buffer_layout& layout)
	: m_vao_id(nullptr, [](GLuint* vao) { glDeleteVertexArrays(1, vao); }),
	m_ebo(ebo), m_vbo(vbo), m_vbo_layout(layout)
{
	auto* vao = new GLuint;
	glGenVertexArrays(1, vao);
	m_vao_id.reset(vao);

	bind();

	m_ebo->bind();
	m_vbo->bind();

	unsigned int i = 0;
	std::size_t offset = 0;

	for (const auto& attribute : m_vbo_layout)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
			attribute.component_count(),
			data_type_to_opengl_type(attribute.get_type()),
			attribute.is_normalised() ? GL_TRUE : GL_FALSE,
			m_vbo_layout.stride(),
			reinterpret_cast<void*>(offset));

		offset += attribute.size();

		++i;
	}

	unbind();
}

void gl::vertex_array::bind() const
{
	glBindVertexArray(*m_vao_id);
}

void gl::vertex_array::unbind() const
{
	glBindVertexArray(0);
}
