#pragma once

#include <vector>

#include "camera.h"
#include "light.h"

class renderer
{
public:
	virtual void render(const camera& camera, const std::vector<light>& lights) = 0;
};
