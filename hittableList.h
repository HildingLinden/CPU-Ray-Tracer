#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable {
public:
	HittableList() {}
	HittableList(std::shared_ptr<Hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }
	
	virtual bool hit(const Ray & ray, double tMin, double tMax, HitRecord & record) const override;

	std::vector<std::shared_ptr<Hittable>> objects;
};

bool HittableList::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
	HitRecord tempRecord;
	bool isAnyHit = false;
	double closestHit = tMax;

	for (const std::shared_ptr<Hittable> &object : objects) {
		if (object->hit(ray, tMin, closestHit, tempRecord)) {
			isAnyHit = true;
			closestHit = tempRecord.time;
			record = tempRecord;
		}
	}

	return isAnyHit;
}