#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "light.h"
#include "renderer.h"

class scene
{
public:

	void render();

	void add_renderer(const std::shared_ptr<renderer> renderer);

	camera& get_camera() { return m_camera; }

private:
	std::vector<std::shared_ptr<renderer>> m_renderers;

	camera m_camera;
	light m_sun;
	std::vector<light> m_lights;
};
