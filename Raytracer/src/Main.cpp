#include "Ray.h"
#include "Vec3f.h"
#include "Constants.h"
#include "Scene.h"
#include "Camera.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void write_color(std::ostringstream &oss , const Vec3f &color)
{
	// Reescale the value acording to the number of samples per pixel and display it
	float r = color.r();
	float g = color.g();
	float b = color.b();

	float scale = 1.0f / SAMPLES;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write the scaled value to [0,255] color component.
	oss << static_cast<int>(256 * std::clamp(r , 0.0f , 0.999f)) << ' '
		<< static_cast<int>(256 * std::clamp(g , 0.0f , 0.999f)) << ' '
		<< static_cast<int>(256 * std::clamp(b , 0.0f , 0.999f)) << '\n';
}

Vec3f get_color(Ray &ray , const SceneObject &world)
{
	// Returns the RGB vector for a given ray: 
	// Shaded based on the normal unit-vector if it hits a sphere, blended background if not
	HitRecord record;
	if (world.hit(ray , 0.0f , infinity , record))
		return 0.5f * (record.normal + Vec3f(1.0f , 1.0f , 1.0f));
	else
	{
		Vec3f unitVector = unit_vector(ray.direction());
		float t = 0.5f * (unitVector.y() + 1.0f);
		return (1.0f - t) * Vec3f(1.0f , 1.0f , 1.0f) + t * Vec3f(0.5f , 0.5f , 0.5f);
	}
}

int main()
{
	std::srand(std::time(nullptr)); //Seeding std::rand()

	std::ofstream outputFile{"output.ppm"};
	std::ostringstream os{};

	ObjectList world;
	world.add(std::make_shared<Sphere>(Vec3f(0.0f , 0.0f , -1.0f) , 0.5f));
	world.add(std::make_shared<Sphere>(Vec3f(0.0f , -100.5f , -1.0f) , 100.0f));

	Camera cam;

	os << "P3\n" << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "\n255\n";

	for (int j{CANVAS_HEIGHT - 1} ; j >= 0 ; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i{} ; i < CANVAS_WIDTH ; i++)
		{
			Vec3f pixelColor(0.0f , 0.0f , 0.0f);

			for (int k{} ; k < SAMPLES ; k++)
			{
				float u = (i + random_float()) / (CANVAS_WIDTH - 1.0f);
				float v = (j + random_float()) / (CANVAS_HEIGHT - 1.0f);
				Ray r = cam.get_ray(u , v);
				pixelColor += get_color(r , world);
			}
			write_color(os , pixelColor);
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