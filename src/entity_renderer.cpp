#include "entity_renderer.h"

#include <glad/glad.h>

#include "material.h"
#include "opengl/texture.h"
#include "opengl/vertex_array.h"

entity_renderer::entity_renderer()
	: m_shader("data/shaders/entity.vert", "data/shaders/entity.frag")
{
	m_shader.bind();

	for (unsigned int i = 0; i < max_lights - 3; ++i)
	{
		//m_shader.set_uniform<glm::vec3>("lights[" + std::to_string(i) + "].position", glm::vec3(-2.0f + i, 1.0f, 1.0f));
		m_shader.set_uniform<glm::vec3>("lights[" + std::to_string(i) + "].position", glm::vec3(-10.0f, 0.0f, 10.0f));
		m_shader.set_uniform<glm::vec3>("lights[" + std::to_string(i) + "].colour", glm::vec3(1.0f));
		m_shader.set_uniform<glm::vec3>("lights[" + std::to_string(i) + "].attenuation", glm::vec3(1.0f, 0.01f, 0.002f));
	}

	//m_shader.set_uniform<glm::vec3>("lights[0].colour", glm::vec3(1.0f, 0.0f, 0.0f));
	//m_shader.set_uniform<glm::vec3>("lights[1].colour", glm::vec3(0.0f, 1.0f, 0.0f));
	//m_shader.set_uniform<glm::vec3>("lights[2].colour", glm::vec3(0.0f, 0.0f, 1.0f));
	//m_shader.set_uniform<glm::vec3>("lights[3].colour", glm::vec3(1.0f, 1.0f, 0.0f));

	m_shader.set_uniform<int>("num_lights", max_lights - 3);

	m_shader.unbind();
}

entity& entity_renderer::create_entity(const std::string& model_name, const glm::vec3& position)
{
	const auto model = m_models.load_model(m_textures, model_name);

	return m_entities[model].emplace_back(position);
}

void entity_renderer::render(const camera& camera, const light& sun, const std::vector<light>& lights)
{
	m_shader.bind();

	m_shader.set_uniform<glm::mat4>("view", camera.get_view_matrix());
	m_shader.set_uniform<glm::mat4>("projection", camera.get_projection_matrix());

	// TODO: Create light object
	//m_shader.set_uniform<glm::vec3>("sun.position", glm::vec3(0.0f, 1.0f, 0.0f));
	//m_shader.set_uniform<glm::vec3>("sun.ambient", glm::vec3(0.1f));
	//m_shader.set_uniform<glm::vec3>("sun.diffuse", glm::vec3(0.5f));
	//m_shader.set_uniform<glm::vec3>("sun.specular", glm::vec3(1.0f));

	m_shader.set_uniform<glm::vec3>("viewer_position", camera.get_position());

	for (const auto& entity_batch : m_entities)
	{
		const auto& vao = entity_batch.first->get_vao();
		const auto& material = entity_batch.first->get_material();

		glActiveTexture(GL_TEXTURE0);
		material.get_diffuse_texture().bind();
		m_shader.set_uniform<int>("diffuse_texture", 0);

		glActiveTexture(GL_TEXTURE1);
		material.get_detail_texture().bind();
		m_shader.set_uniform<int>("detail_texture", 1);

		m_shader.set_uniform<float>("shininess", material.get_shininess());

		vao.bind();

		for (const auto& entity : entity_batch.second)
		{
			m_shader.set_uniform<glm::mat4>("model", entity.get_transformation_matrix());

			glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vao.index_count()), GL_UNSIGNED_INT, nullptr);
		}


		vao.unbind();
	}

	m_shader.unbind();
}
