#pragma once

#include <algorithm>

#include "iostream"
#include "vec3.h"

void writeColor(std::ostream &outStream, Color3 pixelColor, int samplesPerPixel) {
	double r = pixelColor[0];
	double g = pixelColor[1];
	double b = pixelColor[2];

	// Scale each color by the number of samples per pixel
	double scale = 1.0 / samplesPerPixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write each color component of a pixel scaled to between 0 and 255
	outStream	
		<< static_cast<int>(255.999 * std::clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * std::clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(255.999 * std::clamp(b, 0.0, 0.999)) << '\n';
}