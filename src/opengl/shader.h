#pragma once

#include <functional>
#include <memory>
#include <string>
#include <type_traits>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl
{
	class shader
	{
	public:
		// TODO: Replace paths with source code. Create separate class for loading from files
		shader(const std::string& vertex_path, const std::string& fragment_path);

		void bind();
		void unbind();

		template<typename T>
		void set_uniform(const std::string& name, const T& value)
		{
			const auto location = glGetUniformLocation(*m_program_id, name.c_str());

			if constexpr (std::is_same_v<T, int>)
			{
				glUniform1i(location, value);
			}
			else if constexpr (std::is_same_v<T, float>)
			{
				glUniform1f(location, value);
			}
			else if constexpr (std::is_same_v<T, glm::mat4>)
			{
				glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
			}
			else if constexpr (std::is_same_v<T, glm::vec3>)
			{
				glUniform3fv(location, 1, glm::value_ptr(value));
			}
			else
			{
				static_assert(false, "T is not a compatible shader type");
			}
		}

	private:
		enum class type
		{
			vertex,
			geometry,
			fragment,
		};

		std::unique_ptr<GLuint, std::function<void(GLuint*)>> m_program_id;

		std::string load_file(const std::string& path) const;
		GLuint compile_shader(const type type, const std::string& source) const;
	};
}
