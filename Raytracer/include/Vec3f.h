#pragma once

#include <cmath>
#include <iostream>
#include "Constants.h"

class Vec3f
{
public:
	// Overloaded Constructors
	Vec3f()
		: m_x{0.0f} , m_y{0.0f} , m_z{0.0f} {}
	Vec3f(float t)
		: m_x{t} , m_y{t} , m_z{t} {}
	Vec3f(float x , float y , float z)
		: m_x{x} , m_y{y} , m_z{z} {}

	// Getters x, y, z (pos) and r, g, b (color)
	inline float x() const { return m_x; }
	inline float y() const { return m_y; }
	inline float z() const { return m_z; }
	inline float r() const { return m_x; }
	inline float g() const { return m_y; }
	inline float b() const { return m_z; }

	// Length and squared length from the vector
	inline float squared_length() { return m_x * m_x + m_y * m_y + m_z * m_z; }
	inline float length() { return std::sqrt(squared_length()); }

	// Random vector generator
	inline static Vec3f random(float min , float max)
	{
		return Vec3f(random_float(min , max) , random_float(min , max) , random_float(min , max));
	}

	// Function that returns true if the vector is close to zero in all dimentions
	inline bool near_zero() const
	{
		constexpr auto s = 1e-8;
		return (std::fabs(m_x) < s) && (std::fabs(m_y) < s) && (std::fabs(m_z) < s);
	}

	// Print the vector with a friend function
	friend inline std::ostream &operator<<(std::ostream &os , const Vec3f &vec)
	{
		os << "[ " << vec.m_x << " , " << vec.m_y << " , " << vec.m_z << " ]";
		return os;
	}

	// Basic operations as member functions
	inline Vec3f operator-() const { return Vec3f(-m_x , -m_y , -m_z); }
	inline Vec3f &operator+=(const Vec3f &vec)
	{
		m_x += vec.m_x;
		m_y += vec.m_y;
		m_z += vec.m_z;
		return *this;
	}
	inline Vec3f &operator-=(const Vec3f &vec)
	{
		m_x -= vec.m_x;
		m_y -= vec.m_y;
		m_z -= vec.m_z;
		return *this;
	}
	inline Vec3f &operator*=(const float &t)
	{
		m_x *= t;
		m_y *= t;
		m_z *= t;
		return *this;
	}
	inline Vec3f &operator/=(const float &t)
	{
		m_x /= t;
		m_y /= t;
		m_z /= t;
		return *this;
	}

	// Basic operations as friend functions
	friend inline Vec3f operator+(const Vec3f &vec1 , const Vec3f &vec2)
	{
		return Vec3f(vec1.m_x + vec2.m_x , vec1.m_y + vec2.m_y , vec1.m_z + vec2.m_z);
	}

	friend inline Vec3f operator-(const Vec3f &vec1 , const Vec3f &vec2)
	{
		return Vec3f(vec1.m_x - vec2.m_x , vec1.m_y - vec2.m_y , vec1.m_z - vec2.m_z);
	}

	friend inline Vec3f operator*(const Vec3f &vec1 , const Vec3f &vec2)
	{
		return Vec3f(vec1.m_x * vec2.m_x , vec1.m_y * vec2.m_y , vec1.m_z * vec2.m_z);
	}

	friend inline Vec3f operator/(const Vec3f &vec1 , const Vec3f &vec2)
	{
		return Vec3f(vec1.m_x / vec2.m_x , vec1.m_y / vec2.m_y , vec1.m_z / vec2.m_z);
	}

	friend inline Vec3f operator*(const Vec3f &vec , const float &t)
	{
		return Vec3f(vec.m_x * t , vec.m_y * t , vec.m_z * t);
	}

	friend inline Vec3f operator*(const float &t , const Vec3f &vec) { return vec * t; }
	friend inline Vec3f operator/(const Vec3f &vec , const float &t)
	{
		return Vec3f(vec.m_x / t , vec.m_y / t , vec.m_z / t);
	}

	friend inline float dot(const Vec3f &vec1 , const Vec3f &vec2)
	{
		return vec1.m_x * vec2.m_x + vec1.m_y * vec2.m_y + vec1.m_z * vec2.m_z;
	}

	friend inline Vec3f cross(const Vec3f &vec1 , const Vec3f &vec2)
	{
		return Vec3f(vec1.m_y * vec2.m_z - vec1.m_z * vec2.m_y ,
					 -(vec1.m_x * vec2.m_z - vec1.m_z * vec2.m_x) ,
					 vec1.m_x * vec2.m_y - vec1.m_y * vec2.m_x);
	}

private:
	float m_x , m_y , m_z;
};

// Function that makes a unit vector using a given vector as reference
inline Vec3f unit_vector(Vec3f vec) { return vec / vec.length(); }

// Function that generates a unit random vector within a unit length sphere tangent to a hit point
inline Vec3f random_unit_vector()
{
	while (true)
	{
		Vec3f p = Vec3f::random(-1.0f , 1.0f);
		if (p.squared_length() >= 1)
			continue;
		return unit_vector(p);
	}
}

// Function that returns the direction of a reflected ray using "n" as the normal to the hit point
inline Vec3f reflect(const Vec3f &v , const Vec3f &n) { return v - 2 * dot(v , n) * n; }