#pragma once

#include "camera.h"

class renderer
{
public:
	virtual void render(const camera& camera) = 0;
};
