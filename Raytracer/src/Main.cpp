#include "Vec3f.h"
#include <fstream>
#include <sstream>

constexpr int CANVAS_WIDTH = 400;
constexpr int CANVAS_HEIGHT = 200;

int main()
{
	std::ofstream outputFile {"output.ppm"};
	std::ostringstream os{};
	
	os << "P3\n" << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "\n255\n";

	for (int j{CANVAS_HEIGHT - 1} ; j >= 0 ; j--)
	{
		for (int i{} ; i < CANVAS_WIDTH ; i++)
		{
			Vec3f color ((float)j / (CANVAS_HEIGHT - 1.0f) , 
						 (float)i / (CANVAS_WIDTH - 1.0f) , 
						 0.0f);

			int r = (int)(255.0f * color.r());
			int g = (int)(255.0f * color.g());
			int b = (int)(255.0f * color.b());

			os << r << " " << g << " " << b << "\n";
		}
	}

	if (outputFile)
		outputFile << os.str();
	else
		std::cout << "Could not open output file..." << std::endl;

	outputFile.close();

	return 0;
}