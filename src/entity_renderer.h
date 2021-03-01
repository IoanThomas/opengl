#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "camera.h"
#include "entity.h"
#include "model.h"
#include "model_cache.h"
#include "opengl/shader.h"
#include "light.h"
#include "renderer.h"
#include "texture_cache.h"

class entity_renderer : public renderer
{
public:
	static constexpr unsigned int max_lights = 4;

	entity_renderer();

	entity& create_entity(const std::string& model_name, const glm::vec3& position);

	void render(const camera& camera, const light& sun, const std::vector<light>& lights);

private:
	model_cache m_models;
	texture_cache m_textures;

	gl::shader m_shader;
	std::map<std::shared_ptr<model>, std::vector<entity>> m_entities;
};
