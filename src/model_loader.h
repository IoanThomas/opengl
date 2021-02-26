#pragma once

#include <string>
#include <vector>

#include "opengl/vertex_array.h"

class model_loader
{
public:
	static gl::vertex_array load_vao(const std::string& path);

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

	static void process_vertex(const std::vector<std::string>& vertex_str, std::vector<vertex>& vertices, std::vector<unsigned int>& indices);
	static std::vector<std::string> split_string(const std::string& string, const char delimiter);
};
