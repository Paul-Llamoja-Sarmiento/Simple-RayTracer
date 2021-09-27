#pragma once

#include "Vec3f.h"
#include "Ray.h"

struct HitRecord;

class Material
{
	// Abstract class for a generic material. 
public:
	Material(const Vec3f &albedo)
		: m_albedo{albedo} { }

	virtual bool scatter(const Ray &rayIn ,
						 const HitRecord &record ,
						 Vec3f &attenuation ,
						 Ray &scattered) const = 0;

protected:
	Vec3f m_albedo;
};


class Lambertian : public Material
{
	// Class that represents a diffuse material
public:
	Lambertian(const Vec3f &albedo)
		: Material(albedo) { }

	virtual bool scatter(const Ray &rayIn ,
						 const HitRecord &record ,
						 Vec3f &attenuation ,
						 Ray &scatteredRay) const override
	{
		auto scatterDirection = record.normal + random_unit_vector();

		if (scatterDirection.near_zero()) // Catches an error if scatterDirection ~ 0
			scatterDirection = record.normal;

		scatteredRay = Ray(record.point , scatterDirection);
		attenuation = m_albedo;
		return true;
	}
};


class Metal : public Material
{
	// Class that represents a metal surface
public:
	Metal(const Vec3f &albedo , const float &fuzz)
		: Material(albedo) , m_fuzz{fuzz < 1 ? fuzz : 1} { }

	virtual bool scatter(const Ray &rayIn ,
						 const HitRecord &record ,
						 Vec3f &attenuation ,
						 Ray &scatteredRay) const override
	{
		auto scatterDirection = reflect(unit_vector(rayIn.direction()) , record.normal);
		scatteredRay = Ray(record.point , scatterDirection + m_fuzz * random_unit_vector());
		attenuation = m_albedo;
		return (dot(scatteredRay.direction() , record.normal) > 0);
	}

protected:
	float m_fuzz;
};