#pragma once

#include "Vec3f.h"

// Modeling a Ray as: p(t) = A + t * B 
// A: Vec of starting point
// B: Vec of direction
class Ray 
{
public:
	Ray() {}
	Ray(const Vec3f &vec1 , const Vec3f &vec2)
		: A{vec1} , B{unit_vector(vec2)} {}

	inline Vec3f origin() const { return A; }
	inline Vec3f direction() const { return B; }
	Vec3f point_at_parameter(float t) { return A + t * B; }

private:
	Vec3f A;
	Vec3f B;
};