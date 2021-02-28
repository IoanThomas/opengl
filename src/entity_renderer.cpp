#include "entity_renderer.h"

#include <string>

#include "material.h"
#include "model_loader.h"
#include "opengl/texture.h"
#include "opengl/vertex_array.h"

entity_renderer::entity_renderer()
	: m_shader("data/shaders/entity.vert", "data/shaders/entity.frag")
{
}

entity& entity_renderer::create_entity(const std::string& model_name)
{
	// TODO: Cache model
	auto vao = model_loader::load_vao("data/models/" + model_name + '/' + model_name + ".obj");
	const auto diffuse_texture = m_textures.load_texture("data/models/" + model_name + '/' + model_name + ".png");
	const auto specular_texture = m_textures.load_texture("data/models/" + model_name + '/' + model_name + "_spec.png");

	material material(diffuse_texture, specular_texture, 128.0f);

	const auto mod = std::make_shared<model>(std::move(vao), material);
	return m_entities[mod].emplace_back();
}

void entity_renderer::render(const camera& camera)
{
	m_shader.bind();

	const auto projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	m_shader.set_uniform<glm::mat4>("projection", projection);
	m_shader.set_uniform<glm::mat4>("view", camera.get_view_matrix());
	m_shader.set_uniform<glm::vec3>("viewer_position", camera.get_position());

	m_shader.set_uniform<glm::vec3>("sun.position", glm::vec3(1.2f, 1.0f, 2.0f));
	m_shader.set_uniform<glm::vec3>("sun.ambient", glm::vec3(0.2f));
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
		material.m_specular->bind();
		m_shader.set_uniform<int>("specular_texture", 1);

		m_shader.set_uniform<float>("shininess", material.m_shininess);

		vao.bind();

		for (const auto& entity : entity_batch.second)
		{
			m_shader.set_uniform<glm::mat4>("model", entity.get_transformation_matrix());
			//m_shader.set_uniform<glm::mat4>("model", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -1.0f)));

			//const auto i = vao.index_count();

			glDrawElements(GL_TRIANGLES, vao.index_count(), GL_UNSIGNED_INT, nullptr);
		}


		vao.unbind();
	}

	m_shader.unbind();
}
