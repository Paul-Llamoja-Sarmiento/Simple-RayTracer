#include "Scene.h"
#include "Vec3f.h"
#include <cmath>

bool Sphere::hit(const Ray &ray , float tMin , float tMax , HitRecord &record) const
{
	// Algorithm to process whether a ray hits or not a sphere
	// Modeling a Ray as: p(t) = A + t * B 
	// Sphere center : C
	// Sphere equation: t*t*dot(B,B) + 2*t*dot(B,C) + dot(A-C,A-C)-R*R = 0
	Vec3f originCenter = ray.origin() - m_center; // A - C
	float a = dot(ray.direction() , ray.direction());
	float b = 2.0f * dot(ray.direction() , originCenter);
	float c = dot(originCenter , originCenter) - (m_radius * m_radius);
	float discriminant = b * b - (4.0f * a * c);

	if (discriminant < 0)
		return false;

	// Finds the nearest root that lies in range
	float temp = (-b - std::sqrt(discriminant)) / (2.0f * a);

	if (temp < tMin || temp > tMax)
	{
		temp = (-b + std::sqrt(discriminant)) / (2.0f * a);

		if (temp < tMin || temp > tMax)
			return false;
	}

	// Saves the data record of the hit
	record.t = temp;
	record.point = ray.point_at_parameter(record.t);
	record.normal = (record.point - m_center) / m_radius;
	record.set_front_face(ray , record.normal);

	return true;
}


bool ObjectList::hit(const Ray &ray , float tMin , float tMax , HitRecord &record) const
{
	// Algorithm to process wether a ray hits or not an array of scene objects (spheres in this case)
	HitRecord tempRecord;
	bool hitFlag{false};
	float closestSoFar {tMax};

	for (const auto &object : m_objects)
	{
		if (object->hit(ray , tMin , closestSoFar , tempRecord))
		{
			hitFlag = true;
			closestSoFar =tempRecord.t;
			record = tempRecord;
		}
	}

	return hitFlag;
}