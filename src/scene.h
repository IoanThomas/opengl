#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "point_light.h"
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
	std::vector<point_light> m_lights;
};
