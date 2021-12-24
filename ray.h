#pragma once

#include "vec3.h"

class Ray {
public:
	Ray(const Point3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {}

	Point3 getOrigin() const { return origin; }
	Vec3 getDirection() const { return direction; }

	Point3 at(double t) const { return  origin + t * direction; }

	Point3 origin;
	Vec3 direction;
};