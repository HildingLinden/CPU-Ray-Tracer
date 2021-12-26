#pragma once

#include "rtUtil.h"

class Material;

struct HitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> materialPtr;
	double time;
	bool isFrontFace;

	inline void setFaceNormal(const Ray &ray, const Vec3 &outwardsNormal) {
		isFrontFace = dot(ray.getDirection(), outwardsNormal) < 0;
		normal = isFrontFace ? outwardsNormal : -outwardsNormal;
	}
};

class Hittable {
public:
	virtual bool hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const = 0;
};