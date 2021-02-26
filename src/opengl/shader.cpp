#include "shader.h"

#include <fstream>
#include <ios>
#include <sstream>
#include <stdexcept>

gl::shader::shader(const std::string& vertex_path, const std::string& fragment_path)
	: m_program_id(nullptr, [](GLuint* program) { glDeleteProgram(*program); })
{
	const auto vertex_src = load_file(vertex_path);
	const auto fragment_src = load_file(fragment_path);

	const auto vertex_shader = compile_shader(type::vertex, vertex_src);
	const auto fragment_shader = compile_shader(type::fragment, fragment_src);

	GLuint* program = new GLuint(glCreateProgram());
	m_program_id.reset(program);

	glAttachShader(*m_program_id, vertex_shader);
	glAttachShader(*m_program_id, fragment_shader);
	glLinkProgram(*m_program_id);

	// TODO: Put error checking in a separate method
	GLint success;
	char info_log[512];
	glGetProgramiv(*m_program_id, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(*m_program_id, sizeof(info_log), nullptr, info_log);

		// TODO: Replace with custom exception
		throw std::runtime_error(std::string("Failed to link shaders: ") + info_log);
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void gl::shader::bind()
{
	glUseProgram(*m_program_id);
}

void gl::shader::unbind()
{
	glUseProgram(0);
}

std::string gl::shader::load_file(const std::string& path) const
{
	const std::ifstream file_stream(path);
	if (!file_stream)
	{
		throw std::runtime_error(std::string("Failed to load shader \"") + path + "\"");
	}

	std::stringstream ss;
	ss << file_stream.rdbuf();

	return ss.str();
}

GLuint gl::shader::compile_shader(const type type, const std::string& source) const
{
	const auto shader = glCreateShader(type == type::vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);

	glCompileShader(shader);

	// TODO: Put error checking in a separate method
	GLint success;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);

		// TODO: Replace with custom exception
		throw std::runtime_error(std::string("Failed to compile shader: ") + info_log);
	}

	return shader;
}
