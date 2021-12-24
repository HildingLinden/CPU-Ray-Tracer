#pragma once

#include "rtUtil.h"

class Camera {
public:
	Camera() {
		const double imageAspectRatio = 16.0 / 9.0; //TODO: Double aspect ratio declaration?

		// Viewport
		const double viewportHeight = 2.0;
		const double viewportWidth = imageAspectRatio * viewportHeight;
		const double focalLength = 1.0;

		// Member initialization
		origin = Point3(0, 0, 0);
		horizontal = Vec3(viewportWidth, 0, 0);
		vertical = Vec3(0, viewportHeight, 0);
		lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - Vec3(0, 0, focalLength);
	}

	Ray getRay(double u, double v) const {
		return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

private:
	Point3 origin;
	Point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
};