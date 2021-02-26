#include "texture.h"

gl::texture::texture(const unsigned int width, const unsigned int height, const std::vector<uint8_t>& pixels)
	: m_texture_id(nullptr, [](GLuint* texture_id) { glDeleteTextures(1, texture_id); })
{
	auto* texture_id = new GLuint;
	glGenTextures(1, texture_id);
	m_texture_id.reset(texture_id);

	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unbind();
}

void gl::texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, *m_texture_id);
}

void gl::texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
