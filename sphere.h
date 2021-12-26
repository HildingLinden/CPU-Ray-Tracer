#pragma once

#include <cmath>
#include "hittable.h"

class Sphere : public Hittable {
public:
	Sphere() {}
	Sphere(Point3 center, double radius, std::shared_ptr<Material> materialPtr) : center(center), radius(radius), materialPtr(materialPtr) {}

	virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const override;
private:
	Point3 center;
	double radius;
	std::shared_ptr<Material> materialPtr;
};

bool Sphere::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
	// t "time", b Ray direction, A Ray origin, C spehere center, r spehere radius
	// t²b ⋅ b + 2tb ⋅ (A-C) + (A-C) ⋅ (A-C) - r² = 0
	// 0 roots miss, 1 root surface, 2 roots goes through

	// A - C
	Vec3 AC = ray.getOrigin() - center;

	// a,b & c of the quadratic formula to get the discriminant
	// b ⋅ b, vector dotted by itself is length squared
	double a = ray.getDirection().lengthSquared();

	// 2b ⋅ (A-C)
	double halfb = dot(AC, ray.getDirection());

	// (A - C) ⋅ (A - C) - r², vector dotted by itself is length squared
	double c = AC.lengthSquared() - radius * radius;

	double discriminant = halfb * halfb - a * c;

	if (discriminant < 0.0) {
		return false;
	}

	// Find the nearest root of the quadratic formula (half b form) between tMin & tMax
	double sqrtDiscriminant = std::sqrt(discriminant);

	double root = (-halfb - sqrtDiscriminant) / a;
	if (root < tMin || root > tMax) {
		root = (-halfb + sqrtDiscriminant) / a;
		if (root < tMin || root > tMax) {
			return false;
		}
	}

	record.time = root;
	record.point = ray.at(root);
	Vec3 outwardsNormal = (record.point - center) / radius;
	record.setFaceNormal(ray, outwardsNormal);
	record.materialPtr = materialPtr;

	return true;
}