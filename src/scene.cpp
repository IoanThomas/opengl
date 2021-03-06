#include "scene.h"

void scene::render()
{
	for (const auto& renderer : m_renderers)
	{
		renderer->render(m_camera, m_sun, m_lights);
	}
}

void scene::add_renderer(const std::shared_ptr<renderer> renderer)
{
	m_renderers.push_back(renderer);
}
