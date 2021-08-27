#pragma once

#include "Vec3f.h"

// Modeling a Ray as: p(t) = A + t * B 
// p: 3D position along a line when the parameter is "t"
// A: 3D position of the  ray origin
// B: Vec of direction of the line

class Ray
{
public:
	Ray() {}
	Ray(const Vec3f &origin , const Vec3f &direction)
		: m_origin{origin} , m_direction{direction} {}

	inline Vec3f origin() const { return m_origin; }
	inline Vec3f direction() const { return m_direction; }
	inline Vec3f point_at_parameter(float t) const { return m_origin + t * m_direction; }

private:
	Vec3f m_origin;
	Vec3f m_direction;
};