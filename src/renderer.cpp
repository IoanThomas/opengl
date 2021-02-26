#include "renderer.h"

#include <utility>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "material.h"
#include "model_loader.h"
#include "opengl/texture.h"

#include <iostream>

renderer::renderer()
	: m_shader("data/shaders/entity.vert", "data/shaders/entity.frag")
{
}

void renderer::render()
{
	m_shader.bind();

	const auto projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	m_shader.set_uniform<glm::mat4>("projection", projection);
	m_shader.set_uniform<glm::mat4>("view", m_camera.get_view_matrix());
	m_shader.set_uniform<glm::vec3>("viewer_position", m_camera.get_position());

	m_shader.set_uniform<glm::vec3>("sun.position", glm::vec3(1.2f, 1.0f, 2.0f));
	m_shader.set_uniform<glm::vec3>("sun.ambient", glm::vec3(0.2f));
	m_shader.set_uniform<glm::vec3>("sun.diffuse", glm::vec3(0.5f));
	m_shader.set_uniform<glm::vec3>("sun.specular", glm::vec3(1.0f));

	for (const auto& entity_batch : m_entities)
	{
		const auto& vao = entity_batch.first->m_vao;
		const auto& material = entity_batch.first->m_material;

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

void renderer::load_model(const std::string& path)
{
	auto vao = model_loader::load_vao("data/models/" + path + "/" + path + ".obj");
	const auto texture = m_textures.load_texture("data/models/" + path + "/" + path + ".png");
	const auto texture2 = m_textures.load_texture("data/models/" + path + "/" + path + "_spec.png");

	material material(texture, texture2, 128.0f);

	auto mod = std::make_shared<model>(std::move(vao), material);

	entity e;
	//e.position = glm::vec3(1.0f, 0.0f, -1.0f);
	e.position = glm::vec3(0.0f, 0.0f, -1.0f);
	e.scale = glm::vec3(0.2f);

	entity e2;
	//e.position = glm::vec3(1.0f, 0.0f, -1.0f);
	e2.position = glm::vec3(0.0f, 0.0f, -1.5f);
	e2.rotation = glm::vec3(0.0f, 0.0f, 45.0f);
	e2.scale = glm::vec3(0.2f);

	m_entities[mod] = {e, e2};
}
