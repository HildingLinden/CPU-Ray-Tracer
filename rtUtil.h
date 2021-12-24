#pragma once

#include <cmath>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degresToRadians(double degrees) {
	return degrees * pi / 180.0;
}

#include "ray.h"
#include "vec3.h"