#pragma once

#include <cstddef>
#include <functional>
#include <memory>

#include <glad/glad.h>

#include "buffer_layout.h"
#include "element_buffer.h"
#include "vertex_buffer.h"

#include <iostream>

namespace gl
{
	class vertex_array
	{
	public:
		vertex_array(const std::shared_ptr<element_buffer> ebo, const std::shared_ptr<vertex_buffer> vbo, const buffer_layout& layout);

		void bind() const;
		void unbind() const;

		size_t index_count() const { return m_ebo->index_count(); }

	private:
		std::unique_ptr<GLuint, std::function<void(GLuint*)>> m_vao_id;
		std::shared_ptr<element_buffer> m_ebo;
		std::shared_ptr<vertex_buffer> m_vbo;
		buffer_layout m_vbo_layout;
	};
}
