#include "element_buffer.h"

gl::element_buffer::element_buffer(const std::vector<unsigned int>& indices)
	: m_ebo_id(nullptr, [](GLuint* vbo) { glDeleteBuffers(1, vbo); }), m_index_count(indices.size())
{
	auto* ebo = new GLuint;
	glGenBuffers(1, ebo);
	m_ebo_id.reset(ebo);

	bind();

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	unbind();
}

void gl::element_buffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo_id);
}

void gl::element_buffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
