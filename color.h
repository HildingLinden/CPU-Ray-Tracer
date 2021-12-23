#pragma once

#include "iostream"

#include "vec3.h"

void writeColor(std::ostream &outStream, color3 pixelColor) {
	// Write each color component of a pixel scaled to between 0 and 255
	outStream	
		<< static_cast<int>(255.999 * pixelColor[0]) << ' '
		<< static_cast<int>(255.999 * pixelColor[1]) << ' '
		<< static_cast<int>(255.999 * pixelColor[2]) << '\n';
}