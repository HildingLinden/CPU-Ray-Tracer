#pragma once

struct hitRecord {
	point3 p;
	vec3 normal;
	double t;
};

class hittable {
public:
	virtual bool hit(const ray &ray, double tMin, double tMax, hitRecord &record) const = 0;
};