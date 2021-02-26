#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <vector>

#include <glad/glad.h>

namespace gl
{
	class element_buffer
	{
	public:
		friend class vertex_array;

		element_buffer(const std::vector<unsigned int>& indices);

		size_t index_count() const { return m_index_count; }

	private:
		std::unique_ptr<GLuint, std::function<void(GLuint*)>> m_ebo_id;
		size_t m_index_count;

		void bind() const;
		void unbind() const;
	};
}
