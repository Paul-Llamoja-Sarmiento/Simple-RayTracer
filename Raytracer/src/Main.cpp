#include "Ray.h"
#include "Vec3f.h"
#include "Constants.h"
#include <fstream>
#include <sstream>

void write_color(std::ostringstream &oss , const Vec3f &color)
{
	// Write the translated [0,255] value of each color component.
	oss << static_cast<int>(255.999 * color.x()) << ' '
		<< static_cast<int>(255.999 * color.y()) << ' '
		<< static_cast<int>(255.999 * color.z()) << '\n';
}

bool hit_sphere(const Vec3f &sphereCenter , const float &sphereRadius , const Ray &ray)
{
	// Algorithm to process whether a ray hits or not a sphere
	// Modeling a Ray as: p(t) = A + t * B 
	// Sphere center : C
	// Sphere equation: t*t*dot(B,B) + 2*t*dot(B,C) + dot(A-C,A-C)-R*R = 0
	Vec3f originCenter = ray.origin() - sphereCenter; // (A - C)
	float a = dot(ray.direction() , ray.direction());
	float b = 2.0f * dot(ray.direction() , originCenter);
	float c = dot(originCenter , originCenter) - (sphereRadius * sphereRadius);
	float discriminant = (b * b) - (4 * a * c);
	return (discriminant > 0);
}

Vec3f get_color(Ray &ray)
{
	// Returns the RGB vector for a given ray: 
	// Blue if it hits the sphere, red blended background if not
	if (hit_sphere(Vec3f(0.0f , 0.0f , -1.0f) , 0.5f , ray))
		return Vec3f(0.0f , 0.0f , 1.0f);
	else
	{
		Vec3f unitVector = unit_vector(ray.direction());
		float t = 0.5f * (unitVector.y() + 1.0f);
		return (1.0f - t) * Vec3f(1.0f , 1.0f , 1.0f) + t * Vec3f(1.0f , 0.0f , 0.0f);
	}
}

int main()
{
	std::ofstream outputFile{"output.ppm"};
	std::ostringstream os{};

	os << "P3\n" << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "\n255\n";

	for (int j{CANVAS_HEIGHT - 1} ; j >= 0 ; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i{} ; i < CANVAS_WIDTH ; i++)
		{
			float u = static_cast<float>(i) / (CANVAS_WIDTH - 1.0f);
			float v = static_cast<float>(j) / (CANVAS_HEIGHT - 1.0f);

			Ray r(ORIGIN , LOWER_LEFT_CORNER + u * HORIZONTAL + v * VERTICAL);
			Vec3f color = get_color(r);
			write_color(os , color);
		}
	}

	std::cerr << "\nDone.\n";

	if (outputFile)
		outputFile << os.str();
	else
		std::cout << "Could not open output file..." << std::endl;

	outputFile.close();

	return 0;
}