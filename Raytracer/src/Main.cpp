#include "Ray.h"
#include <fstream>
#include <sstream>

constexpr int CANVAS_WIDTH = 400;
constexpr int CANVAS_HEIGHT = 200;

Vec3f get_color(Ray &ray)
{
	float t = 0.5f * (ray.direction().y() + 1.0f);
	return (1.0f - t) * Vec3f(1.0f , 1.0f , 1.0f) + t * Vec3f(0.5f , 0.7f , 1.0f);
}

int main()
{
	std::ofstream outputFile {"output.ppm"};
	std::ostringstream os{};
	
	os << "P3\n" << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "\n255\n";

	// Canvas parameters
	Vec3f lowerLeftCorner(-2.0f , -1.0f , -1.0f);
	Vec3f horizontal(4.0f , 0.0f , 0.0f);
	Vec3f vertical(0.0f , 2.0f , 0.0f);
	// Camera eye
	Vec3f origin(0.0f , 0.0f , 0.0f);

	for (int j{CANVAS_HEIGHT - 1} ; j >= 0 ; j--)
	{
		for (int i{} ; i < CANVAS_WIDTH ; i++)
		{
			float u = (float)i / (CANVAS_WIDTH - 1.0f);
			float v = (float)j / (CANVAS_HEIGHT - 1.0f); 
						
			Ray r(origin , lowerLeftCorner + u * horizontal + v * vertical);
			Vec3f color = get_color(r);

			int ir = (int)(255.0f * color.r());
			int ig = (int)(255.0f * color.g());
			int ib = (int)(255.0f * color.b());

			os << ir << " " << ig << " " << ib << "\n";
		}
	}

	if (outputFile)
		outputFile << os.str();
	else
		std::cout << "Could not open output file..." << std::endl;

	outputFile.close();

	return 0;
}