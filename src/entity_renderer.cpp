#include "entity_renderer.h"

#include <string>

#include <glad/glad.h>

#include "material.h"
#include "opengl/texture.h"
#include "opengl/vertex_array.h"

entity_renderer::entity_renderer()
	: m_shader("data/shaders/entity.vert", "data/shaders/entity.frag")
{
}

entity& entity_renderer::create_entity(const std::string& model_name, const glm::vec3& position)
{
	const auto model = m_models.load_model(m_textures, model_name);

	return m_entities[model].emplace_back(position);
}

void entity_renderer::render(const camera& camera)
{
	m_shader.bind();

	// TODO: Move projection matrix somewhere else (camera?)
	const auto projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	m_shader.set_uniform<glm::mat4>("projection", projection);
	m_shader.set_uniform<glm::mat4>("view", camera.get_view_matrix());
	m_shader.set_uniform<glm::vec3>("viewer_position", camera.get_position());

	// TODO: Create light object
	m_shader.set_uniform<glm::vec3>("sun.position", glm::vec3(0.0f, 1.0f, 0.0f));
	//m_shader.set_uniform<glm::vec3>("sun.ambient", glm::vec3(0.05f, 0.02f, 0.01f));
	//m_shader.set_uniform<glm::vec3>("sun.diffuse", glm::vec3(0.46f, 0.3f, 0.05f));
	m_shader.set_uniform<glm::vec3>("sun.ambient", glm::vec3(0.1f));
	m_shader.set_uniform<glm::vec3>("sun.diffuse", glm::vec3(0.5f));
	m_shader.set_uniform<glm::vec3>("sun.specular", glm::vec3(1.0f));

	for (const auto& entity_batch : m_entities)
	{
		const auto& vao = entity_batch.first->get_vao();
		const auto& material = entity_batch.first->get_material();

		glActiveTexture(GL_TEXTURE0);
		material.m_diffuse->bind();
		m_shader.set_uniform<int>("diffuse_texture", 0);

		glActiveTexture(GL_TEXTURE1);
		material.m_detail->bind();
		m_shader.set_uniform<int>("detail_texture", 1);

		m_shader.set_uniform<float>("shininess", material.m_shininess);

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
