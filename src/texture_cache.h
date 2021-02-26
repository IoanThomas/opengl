#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "opengl/texture.h"

class texture_cache
{
public:
	std::shared_ptr<gl::texture> load_texture(const std::string& path);

private:
	std::unordered_map<std::string, std::shared_ptr<gl::texture>> m_textures;
};
