// Solid Quad class interface
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "Solid.h"

// ================================ Quad Solid Class ================================
/**
	* @brief Quadrilateral Solid class
	* @ingroup modulePrimitive
	*/
class CSolidQuad : public CSolid {
public:
	/**
		* @brief Constructor
		* @param pShader Pointer to the shader to be applied for the solid
		* @param a Position of the first vertex
		* @param b Position of the second vertex
		* @param c Position of the third vertex
		* @param d Position of the forth vertex
		*/
	CSolidQuad(const ptr_shader_t pShader, const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d)
	{
		add(std::make_shared<CPrimTriangle>(pShader, a, b, c));
		add(std::make_shared<CPrimTriangle>(pShader, a, c, d));
	}
	virtual ~CSolidQuad(void) = default;
};
