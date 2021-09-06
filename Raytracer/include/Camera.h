#pragma once

#include "Vec3f.h"
#include "Constants.h"
#include "Ray.h"

class Camera
{
public:
	Camera()
		: m_origin{Vec3f(0.0f , 0.0f , 0.0f)} ,
		m_viewportHeight{2.0f} , m_focalLength{1.0f}
	{

		m_viewportWidth = m_viewportHeight * ASPECT_RATIO;
		m_horizontal = Vec3f(m_viewportWidth , 0.0f , 0.0f);
		m_vertical = Vec3f(0.0f , m_viewportHeight , 0.0f);

		m_lowerLeftCorner = m_origin -
			m_horizontal / 2.0f -
			m_vertical / 2.0f -
			Vec3f(0.0f , 0.0f , m_focalLength);
	}

	Ray get_ray(float &u , float &v) const
	{
		return Ray(m_origin , m_lowerLeftCorner + u * m_horizontal + v * m_vertical);
	}
private:
	float m_viewportHeight;
	float m_viewportWidth;
	float m_focalLength;

	Vec3f m_origin;
	Vec3f m_lowerLeftCorner;
	Vec3f m_horizontal;
	Vec3f m_vertical;
};