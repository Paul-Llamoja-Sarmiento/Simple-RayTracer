#pragma once

#include "Vec3f.h"
#include "Constants.h"
#include "Ray.h"

class Camera
{
public:
	Camera(Vec3f lookFrom ,
		   Vec3f lookAt ,
		   Vec3f viewUp ,
		   float verticalFieldOfView ,
		   float aspectRatio)
	{
		// Canvas(viewport) dimensions
		float theta = degrees_to_radians(verticalFieldOfView);
		float viewportHeight = 2.0f * tan(theta / 2);
		float viewportWidth = viewportHeight * aspectRatio;
		float focalLength = 1.0f;

		// Coordinate System from the canvas
		Vec3f w = unit_vector(lookFrom - lookAt);
		Vec3f u = unit_vector(cross(viewUp , w));
		Vec3f v = cross(w , u);

		m_origin = lookFrom;
		m_horizontal = viewportWidth * u;
		m_vertical = viewportHeight * v;

		m_lowerLeftCorner = m_origin -
							m_horizontal / 2.0f -
							m_vertical / 2.0f -
							focalLength * w;
	}

	Ray get_ray(float &u , float &v) const
	{
		return Ray(m_origin , m_lowerLeftCorner + u * m_horizontal + v * m_vertical - m_origin);
	}

private:
	Vec3f m_origin;
	Vec3f m_lowerLeftCorner;
	Vec3f m_horizontal;
	Vec3f m_vertical;
};