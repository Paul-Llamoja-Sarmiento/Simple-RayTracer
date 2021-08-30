#include "Ray.h"
#include "Vec3f.h"
#include "Constants.h"
#include "Scene.h"
#include <fstream>
#include <sstream>

void write_color(std::ostringstream &oss , const Vec3f &color)
{
	// Write the translated [0,255] value of each color component.
	oss << static_cast<int>(255.999 * color.x()) << ' '
		<< static_cast<int>(255.999 * color.y()) << ' '
		<< static_cast<int>(255.999 * color.z()) << '\n';
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
	std::ofstream outputFile{"output.ppm"};
	std::ostringstream os{};

	ObjectList world;
	world.add(std::make_shared<Sphere>(Vec3f(0.0f , 0.0f , -1.0f) , 0.5f));
	world.add(std::make_shared<Sphere>(Vec3f(0.0f , -100.5f , -1.0f) , 100.0f));

	os << "P3\n" << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "\n255\n";

	for (int j{CANVAS_HEIGHT - 1} ; j >= 0 ; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i{} ; i < CANVAS_WIDTH ; i++)
		{
			float u = static_cast<float>(i) / (CANVAS_WIDTH - 1.0f);
			float v = static_cast<float>(j) / (CANVAS_HEIGHT - 1.0f);

			Ray r(ORIGIN , LOWER_LEFT_CORNER + u * HORIZONTAL + v * VERTICAL);
			Vec3f color = get_color(r , world);
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