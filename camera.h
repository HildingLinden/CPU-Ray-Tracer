#pragma once

#include "rtUtil.h"

class Camera {
public:
	Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double verticalFOV, double aspectRatio) {
		double theta = degresToRadians(verticalFOV);
		double h = std::tan(theta / 2.0);
		const double viewportHeight = 2.0 * h;
		const double viewportWidth = aspectRatio * viewportHeight;
		
		Vec3 w = unitVector(lookFrom - lookAt);
		Vec3 u = unitVector(cross(viewUp, w));
		Vec3 v = cross(w, u);

		origin = lookFrom;
		horizontal = viewportWidth * u;
		vertical = viewportHeight * v;
		lowerLeftCorner = origin - horizontal / 2.0 - vertical / 2.0 - w;
	}

	Ray getRay(double s, double t) const {
		return Ray(origin, lowerLeftCorner + s * horizontal + t * vertical - origin);
	}

private:
	Point3 origin;
	Point3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
};