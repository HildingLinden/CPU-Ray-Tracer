#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degresToRadians(double degrees) {
	return degrees * pi / 180.0;
}

inline double randomDouble() {
	static std::mt19937 generator;
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	return distribution(generator);
}

#include "ray.h"
#include "vec3.h"