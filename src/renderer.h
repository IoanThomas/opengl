#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "camera.h"
#include "entity.h"
#include "model.h"
#include "opengl/shader.h"
#include "texture_cache.h"

class renderer
{
public:
	renderer();

	void render();

	void set(const camera& cam) { m_camera = cam; }
	void load_model(const std::string& path);

private:
	texture_cache m_textures;

	camera m_camera;
	gl::shader m_shader;
	std::map<std::shared_ptr<model>, std::vector<entity>> m_entities;
};
