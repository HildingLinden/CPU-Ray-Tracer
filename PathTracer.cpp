#include <string>
#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

double hitSphere(const point3 &center, double radius, const ray &ray) {
    // t "time", b ray direction, A ray origin, C spehere center, r spehere radius
    // t²b ⋅ b + 2tb ⋅ (A-C) + (A-C) ⋅ (A-C) - r² = 0
    // 0 roots miss, 1 root surface, 2 roots goes through

    // A - C
    vec3 AC = ray.getOrigin() - center;

    // a,b & c of the quadratic formula to get the discriminant
    // b ⋅ b, vector dotted by itself is length squared
    double a = ray.getDirection().lengthSquared();

    // 2b ⋅ (A-C)
    double halfb = dot(AC, ray.getDirection());

    // (A - C) ⋅ (A - C) - r², vector dotted by itself is length squared
    double c = AC.lengthSquared() - radius * radius;

    double discriminant = halfb * halfb - a * c;

    if (discriminant < 0.0) {
        return -1.0;
    }
    else {
        // Returning the root of the quadratic formula (half b form)
        return (-halfb - std::sqrt(discriminant)) / a;
    }
}

color3 rayColor(const ray &ray) {
    double t = hitSphere(point3(0, 0, -1), 0.3, ray);

    // Early return if sphere is hit
    if (t > 0.0) {
        vec3 normal = unitVector(ray.at(t) - vec3(0, 0, -1));
        // Get rgb normalized between 0 and 1
        return 0.5 * color3(normal[0] + 1.0, normal[1] + 1.0, normal[2] + 1.0);
    }
    vec3 unitDirection = unitVector(ray.getDirection());

    // Get Y normalized between 0 and 1
    t = 0.5 * (unitDirection[1] + 1.0);

    // Linear interpolation between white and blue
    return (1.0 - t) * color3(1.0, 1.0, 1.0) + t * color3(0.5, 0.7, 1.0);
}

int main()
{

    // Image
    const double imageAspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / imageAspectRatio);

    // Viewport
    const double viewportHeight = 2.0;
    const double viewportWidth = imageAspectRatio * viewportHeight;
    const double focalLength = 1.0;

    const point3 origin = point3(0, 0, 0);
    const vec3 horizontal = vec3(viewportWidth, 0, 0);
    const vec3 vertical = vec3(0, viewportHeight, 0);
    const vec3 lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - vec3(0, 0, focalLength);

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
            double rayX = static_cast<double>(x) / (imageWidth-1);
            double rayY = static_cast<double>(y) / (imageHeight-1);

            ray ray(origin, lowerLeftCorner + rayX * horizontal + rayY * vertical - origin);
            color3 pixelColor = rayColor(ray);
            writeColor(outputFile, pixelColor);
        }
    }

    std::cout << "\nDone!" << std::endl;

    outputFile.close();
}