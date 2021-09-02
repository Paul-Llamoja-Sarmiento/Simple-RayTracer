#pragma once

#include "Ray.h"
#include <memory>
#include <vector>

struct HitRecord
{
	// Saves the information when a ray hits an object
	float t;
	Vec3f point;
	Vec3f normal; // We asume normal always points out
	bool isRayInFront;

	inline void set_front_face(const Ray &ray , const Vec3f normal)
	{
		dot(ray.direction() , normal) > 0 ? isRayInFront = false : isRayInFront = true;
	}
};


class SceneObject
{
	// Abstract class of a general Scene Object
public:
	virtual bool hit(const Ray &ray , float tMin , float tMax , HitRecord &record) const = 0;
};


class Sphere : public SceneObject
{
	// Sphere class, concrete class derived from the abstract SceneObject class
public:
	Sphere() {}
	Sphere(Vec3f center , float radius)
		: m_center{center} , m_radius{radius} {}

	virtual bool hit(const Ray &ray , float tMin , float tMax , HitRecord &record) const override;


private:
	Vec3f m_center;
	float m_radius;
};

class ObjectList : public SceneObject
{
	// Array of concrete objects class, treated like a "concrete object"
public:
	ObjectList() {}
	ObjectList(std::shared_ptr<SceneObject> object) { add(object); }

	inline void clear() { m_objects.clear(); }
	inline void add(std::shared_ptr<SceneObject> object) { m_objects.push_back(object); }
	virtual bool hit(const Ray &ray , float tMin , float tMax , HitRecord &record) const override;

private:
	std::vector<std::shared_ptr<SceneObject>> m_objects;
};