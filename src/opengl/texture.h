#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

#include <glad/glad.h>

namespace gl
{
	class texture
	{
	public:
		texture(const unsigned int width, const unsigned int height, const std::vector<uint8_t>& pixels);
		void bind() const;
		void unbind() const;
	private:
		std::unique_ptr<GLuint, std::function<void(GLuint*)>> m_texture_id;

		
	};
}
