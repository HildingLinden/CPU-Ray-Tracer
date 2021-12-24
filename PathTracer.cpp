#include <string>
#include <iostream>
#include <fstream>

#include "rtUtil.h"
#include "color.h"
#include "hittableList.h"
#include "sphere.h"
#include "camera.h"

Color3 rayColor(const Ray &ray, const Hittable &world) {
	HitRecord record;

	// Hittable or HittableList hit()
	if (world.hit(ray, 0, infinity, record)) {
		return 0.5 * (record.normal + Color3(1, 1, 1));
	}
	
	Vec3 unitDirection = unitVector(ray.getDirection());

	// Get Y normalized between 0 and 1
	double t = 0.5 * (unitDirection[1] + 1.0);

	// Linear interpolation between white and blue
	return (1.0 - t) * Color3(1.0, 1.0, 1.0) + t * Color3(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	const double imageAspectRatio = 16.0 / 9.0;
	const int imageWidth = 400;
	const int imageHeight = static_cast<int>(imageWidth / imageAspectRatio);
	const int samplesPerPixel = 1000;

	// World
	HittableList world;
	world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
	world.add(std::make_shared<Sphere>(Point3(0,-100.5,-1), 100));

	Camera camera;

	// Output setup
	const std::string ppmMagicNumber = "P3";
	const int maxColor = 255;

	std::ofstream outputFile;
	std::string outFileName("picture.ppm");
	outputFile.open(outFileName);
	std::cout << "Writing to file: " << outFileName << std::endl;

	// PPM header
	outputFile << ppmMagicNumber << "\n" << imageWidth << " " << imageHeight << "\n" << maxColor << "\n";

	// Render PPM pixel data
	for (int y = imageHeight - 1; y >= 0; y--) {
		std::cout << "\rRows of pixels remaining: " << y << " " << std::flush;
		for (int x = 0; x < imageWidth; x++) {;
			
			Color3 pixelColor(0, 0, 0);

			for (int i = 0; i < samplesPerPixel; i++) {
				double rayX = (x + randomDouble()) / (imageWidth - 1);
				double rayY = (y + randomDouble()) / (imageHeight - 1);
				Ray ray = camera.getRay(rayX, rayY);
				pixelColor += rayColor(ray, world);
			}
			writeColor(outputFile, pixelColor, samplesPerPixel);
		}
	}

	std::cout << "\nDone!" << std::endl;

	outputFile.close();
}