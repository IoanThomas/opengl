#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "camera.h"
#include "entity.h"
#include "model.h"
#include "model_cache.h"
#include "opengl/shader.h"
#include "renderer.h"
#include "texture_cache.h"

class entity_renderer : public renderer
{
public:
	entity_renderer();

	entity& create_entity(const std::string& model_name);

	void render(const camera& camera);

private:
	model_cache m_models;
	texture_cache m_textures;

	gl::shader m_shader;
	std::map<std::shared_ptr<model>, std::vector<entity>> m_entities;
};
