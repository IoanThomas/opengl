#include "model_loader.h"

#include <algorithm>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <glm/glm.hpp>

#include "opengl/buffer_attribute.h"
#include "opengl/buffer_layout.h"
#include "opengl/element_buffer.h"
#include "opengl/vertex_buffer.h"

gl::vertex_array model_loader::load_vao(const std::string& path)
{
	std::ifstream file_stream(path);
	if (!file_stream)
	{
		throw std::runtime_error(std::string("Failed to load model \"") + path + "\"");
	}

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;

	std::vector<vertex> vertices;
	std::vector<float> vertex_data;
	std::vector<unsigned int> indices;

	std::string line;
	while (std::getline(file_stream, line))
	{
		const auto split_line = split_string(line, ' ');

		if (split_line[0] == "v")
		{
			positions.emplace_back(std::stof(split_line[1]), std::stof(split_line[2]), std::stof(split_line[3]));
		}
		else if (split_line[0] == "vt")
		{
			textures.emplace_back(std::stof(split_line[1]), std::stof(split_line[2]));
		}
		else if (split_line[0] == "vn")
		{
			normals.emplace_back(std::stof(split_line[1]), std::stof(split_line[2]), std::stof(split_line[3]));
		}
		else if (split_line[0] == "f")
		{
			const auto vertex1 = split_string(split_line[1], '/');
			const auto vertex2 = split_string(split_line[2], '/');
			const auto vertex3 = split_string(split_line[3], '/');

			process_vertex(vertex1, vertices, indices);
			process_vertex(vertex2, vertices, indices);
			process_vertex(vertex3, vertices, indices);
		}
	}

	for (const auto& f : vertices)
	{
		vertex_data.push_back(positions.at(f.position_index).x);
		vertex_data.push_back(positions.at(f.position_index).y);
		vertex_data.push_back(positions.at(f.position_index).z);

		vertex_data.push_back(textures.at(f.texture_index).x);
		vertex_data.push_back(textures.at(f.texture_index).y);

		vertex_data.push_back(normals.at(f.normal_index).x);
		vertex_data.push_back(normals.at(f.normal_index).y);
		vertex_data.push_back(normals.at(f.normal_index).z);
	}

	const auto ebo = std::make_shared<gl::element_buffer>(indices);
	const auto vbo = std::make_shared<gl::vertex_buffer>(vertex_data);
	gl::buffer_layout layout = {
		gl::buffer_attribute(gl::data_type::float3),
		gl::buffer_attribute(gl::data_type::float2),
		gl::buffer_attribute(gl::data_type::float3)
	};

	return gl::vertex_array(ebo, vbo, layout);
}

void model_loader::process_vertex(const std::vector<std::string>& vertex_str, std::vector<vertex>& vertices, std::vector<unsigned int>& indices)
{
	vertex vertex;
	vertex.position_index = static_cast<unsigned int>(std::stoi(vertex_str[0])) - 1;
	vertex.texture_index = static_cast<unsigned int>(std::stoi(vertex_str[1])) - 1;
	vertex.normal_index = static_cast<unsigned int>(std::stoi(vertex_str[2])) - 1;

	const auto itr = std::find(vertices.cbegin(), vertices.cend(), vertex);
	if (itr == vertices.cend())
	{
		vertices.push_back(vertex);
	}

	const auto index = std::distance(vertices.cbegin(), std::find(vertices.cbegin(), vertices.cend(), vertex));
	indices.push_back(index);
}

std::vector<std::string> model_loader::split_string(const std::string& string, const char delimiter)
{
	std::vector<std::string> components;
	std::stringstream ss(string);

	std::string part;
	while (std::getline(ss, part, delimiter))
	{
		components.push_back(part);
	}

	return components;
}
