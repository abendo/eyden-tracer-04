#pragma once

#include "SolidQuad.h"

class CSolidSphere : public CSolid
{
public:
	CSolidSphere(ptr_shader_t pShader, const Vec3f& origin = Vec3f::all(0), float radius = 1, size_t sides = 24)
	{
		// --- PUT YOUR CODE HERE ---
	}
	virtual ~CSolidSphere(void) = default;
};