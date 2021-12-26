#include <string>
#include <iostream>
#include <fstream>

#include "rtUtil.h"
#include "color.h"
#include "hittableList.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

Color3 rayColor(const Ray &ray, const Hittable &world, int depth) {
	HitRecord record;

	if (depth <= 0) {
		return Color3(0, 0, 0);
	}
	// Hittable or HittableList hit()
	if (world.hit(ray, 0.001, infinity, record)) {
		Ray scatteredRay;
		Color3 attenuation;
		if (record.materialPtr->scatter(ray, record, attenuation, scatteredRay)) {
			return attenuation * rayColor(scatteredRay, world, depth - 1);
		}
		return Color3(0, 0, 0);
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
	const int samplesPerPixel = 500;
	const int maxDepth = 50;

	// World
	HittableList world;
	auto material_ground = std::make_shared<Lambertian>(Color3(0.2, 0.8, 0.0));
	auto material_center = std::make_shared<Lambertian>(Color3(0.3, 0.4, 0.8));
	auto material_left = std::make_shared<Dielectric>(1.5);
	auto material_right = std::make_shared<Metal>(Color3(0.8, 0.8, 0.8), 0.3);

	world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.4, material_left));
	world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));


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
				pixelColor += rayColor(ray, world, maxDepth);
			}
			writeColor(outputFile, pixelColor, samplesPerPixel);
		}
	}

	std::cout << "\nDone!" << std::endl;

	outputFile.close();
}