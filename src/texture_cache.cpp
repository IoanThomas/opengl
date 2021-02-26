#include "texture_cache.h"

#include <cstdint>
#include <iostream>
#include <vector>

#include "stb_image.h"
#include "texture_cache.h"

std::shared_ptr<gl::texture> texture_cache::load_texture(const std::string& path)
{
	if (m_textures.find(path) != m_textures.cend())
	{
		return m_textures[path];
	}

	stbi_set_flip_vertically_on_load(true);

	const int requested_channels = STBI_rgb_alpha;

	int texture_width;
	int texture_height;
	int num_channels;
	auto* raw_data = stbi_load(path.c_str(), &texture_width, &texture_height, &num_channels, requested_channels);

	//if (!raw_data)
	//{
	//	std::cout << stbi_failure_reason();
	//}

	const int data_size = texture_width * texture_height * requested_channels;
	std::vector<uint8_t> data(raw_data, raw_data + data_size);

	const auto texture = std::make_shared<gl::texture>(texture_width, texture_height, data);
	m_textures[path] = texture;

	stbi_image_free(raw_data);

	return texture;
}
