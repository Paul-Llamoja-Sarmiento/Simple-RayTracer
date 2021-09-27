#pragma once

#include <limits>
#include <cstdlib>
#include <ctime>


// Number constants
constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float PI = 3.1415926f;

// Degrees to radians function converter
inline float degrees_to_radians(float degrees)
{
	return degrees * PI / 180.0f;
}

// Random number generator functions
inline float random_float()
{
	// Returns a random real in [0,1)
	return std::rand() / (RAND_MAX + 1.0f);
}
inline float random_float(float min , float max)
{
	// Returns a random real in [min,max)
	return min + (max - min) * random_float();
}

// Canvas parameters (image) - Pixels
constexpr float ASPECT_RATIO = 16.0f / 9.0f;
constexpr int CANVAS_HEIGHT = 400;
constexpr int CANVAS_WIDTH = static_cast<int>(CANVAS_HEIGHT * ASPECT_RATIO);
constexpr int SAMPLES = 100; // Samples per Pixels for antialiasing
constexpr int MAX_DEPTH = 50; // Max recursion depth in get_color() function