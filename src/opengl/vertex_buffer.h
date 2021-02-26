#pragma once

#include <functional>
#include <memory>
#include <vector>

#include <glad/glad.h>

namespace gl
{
	class vertex_buffer
	{
	public:
		friend class vertex_array;

		vertex_buffer(const std::vector<float>& vertices);

	private:
		std::unique_ptr<GLuint, std::function<void(GLuint*)>> m_vbo_id;

		void bind() const;
		void unbind() const;
	};
}
