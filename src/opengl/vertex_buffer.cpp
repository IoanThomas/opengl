#include "vertex_buffer.h"

gl::vertex_buffer::vertex_buffer(const std::vector<float>& vertices)
	: m_vbo_id(nullptr, [](GLuint* vbo) { glDeleteBuffers(1, vbo); })
{
	// There must be a cleaner way of doing this
	auto* vbo = new GLuint;
	glGenBuffers(1, vbo);
	m_vbo_id.reset(vbo);

	bind();

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	unbind();
}

void gl::vertex_buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, *m_vbo_id);
}

void gl::vertex_buffer::unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
