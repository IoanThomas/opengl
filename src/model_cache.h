#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "model.h"
#include "opengl/vertex_array.h"
#include "texture_cache.h"

class model_cache
{
public:
	std::shared_ptr<model> load_model(texture_cache& textures, const std::string& model_name);
	gl::vertex_array load_vao(const std::string& path);

private:
	struct vertex
	{
	public:
		unsigned int position_index;
		unsigned int texture_index;
		unsigned int normal_index;
		
		bool operator==(const vertex& other) const
		{
			return (position_index == other.position_index) && (texture_index == other.texture_index) && (normal_index == other.normal_index);
		}
	};

	std::unordered_map<std::string, std::shared_ptr<model>> m_models;

	void process_vertex(const std::vector<std::string>& vertex_str, std::vector<vertex>& vertices, std::vector<unsigned int>& indices);
	std::vector<std::string> split_string(const std::string& string, const char delimiter);
};
