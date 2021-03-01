#pragma once

#include <vector>

#include "camera.h"
#include "point_light.h"

class renderer
{
public:
	virtual void render(const camera& camera, const std::vector<point_light>& lights) = 0;
};
