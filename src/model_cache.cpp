#include "model_cache.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <glm/glm.hpp>

#include "opengl/buffer_attribute.h"
#include "opengl/buffer_layout.h"
#include "opengl/element_buffer.h"
#include "opengl/vertex_buffer.h"
#include "material.h"

std::shared_ptr<model> model_cache::load_model(texture_cache& textures, const std::string& model_name)
{
	if (m_models.find(model_name) != m_models.cend())
	{
		return m_models[model_name];
	}

	const auto model_path = "data/models/" + model_name + '/' + model_name;

	auto vao = load_vao(model_path + ".obj");
	const auto diffuse_texture = textures.load_texture(model_path + ".png");
	const auto detail_texture = textures.load_texture(model_path + "_se.png");

	// TODO: Load shininess from file
	const material material(diffuse_texture, detail_texture, 32.0f);
	const auto mod = std::make_shared<model>(std::move(vao), material);

	m_models[model_name] = mod;

	return mod;
}

gl::vertex_array model_cache::load_vao(const std::string& path)
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

	for (const auto& vertex : vertices)
	{
		vertex_data.push_back(positions.at(vertex.position_index).x);
		vertex_data.push_back(positions.at(vertex.position_index).y);
		vertex_data.push_back(positions.at(vertex.position_index).z);

		vertex_data.push_back(textures.at(vertex.texture_index).x);
		vertex_data.push_back(textures.at(vertex.texture_index).y);

		vertex_data.push_back(normals.at(vertex.normal_index).x);
		vertex_data.push_back(normals.at(vertex.normal_index).y);
		vertex_data.push_back(normals.at(vertex.normal_index).z);
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

void model_cache::process_vertex(const std::vector<std::string>& vertex_str, std::vector<vertex>& vertices, std::vector<unsigned int>& indices)
{
	vertex vertex;
	vertex.position_index = static_cast<unsigned int>(std::stoi(vertex_str[0])) - 1;
	vertex.texture_index = static_cast<unsigned int>(std::stoi(vertex_str[1])) - 1;
	vertex.normal_index = static_cast<unsigned int>(std::stoi(vertex_str[2])) - 1;

	const auto itr = std::find(vertices.cbegin(), vertices.cend(), vertex);
	if (itr == vertices.cend())
	{
		vertices.push_back(vertex);
		indices.push_back(vertices.size() - 1);
	}
	else
	{
		const auto index = std::distance(vertices.cbegin(), itr);
		indices.push_back(static_cast<unsigned int>(index));
	}
}

std::vector<std::string> model_cache::split_string(const std::string& string, const char delimiter)
{
	std::vector<std::string> components;
	components.reserve(4);

	std::stringstream ss(string);

	std::string part;
	while (std::getline(ss, part, delimiter))
	{
		components.push_back(part);
	}

	return components;
}
