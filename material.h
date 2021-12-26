#pragma once

#include <algorithm>

#include "rtUtil.h"
#include "hittable.h"

class Material {
public:
	virtual bool scatter(const Ray &ray, const HitRecord &record, Color3 &attenuation, Ray &scatteredRay) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const Color3 &albedo) : albedo(albedo) {}

	virtual bool scatter(const Ray &ray, const HitRecord &record, Color3 &attenuation, Ray &scatteredRay) const override {
		// Chose random point inside the unit sphere that is centered around the unti normal from the hit point
		Vec3 scatterDirection = record.normal + randomPointOnUnitSphere();

		if (scatterDirection.nearZero()) {
			scatterDirection = record.normal;
		}

		scatteredRay = Ray(record.point, scatterDirection);
		attenuation = albedo;
		return true;
	}

	Color3 albedo;
};

class Metal : public Material {
public:
	Metal(const Color3 &albedo, double fuzz) : albedo(albedo), fuzz(std::min(fuzz, 1.0)) {}

	virtual bool scatter(const Ray &ray, const HitRecord &record, Color3 &attenuation, Ray &scatteredRay) const override {
		Vec3 reflected = reflect(unitVector(ray.getDirection()), record.normal);
		// Add some randomness with fuzz
		scatteredRay = Ray(record.point, reflected + fuzz * randomPointInUnitSphere());
		attenuation = albedo;
		return (dot(scatteredRay.getDirection(), record.normal) > 0);
	}

	Color3 albedo;
	double fuzz;
};

class Dielectric : public Material {
public:
	Dielectric(double indexOfRefraction) : indexOfRefraction(indexOfRefraction) {}

	virtual bool scatter(const Ray &ray, const HitRecord &record, Color3 &attenuation, Ray &scatteredRay) const override {
		attenuation = Color3(1.0, 1.0, 1.0);
		double refractionRatio = record.isFrontFace ? (1.0 / indexOfRefraction) : indexOfRefraction;

		Vec3 unitDirection = unitVector(ray.getDirection());
		double cosTheta = std::fmin(dot(-unitDirection, record.normal), 1.0);
		double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

		bool cannotRefract = (refractionRatio * sinTheta) > 1.0;
		Vec3 direction;

		if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble()) {
			direction = reflect(unitDirection, record.normal);
		}
		else {
			direction = refract(unitDirection, record.normal, refractionRatio);
		}

		scatteredRay = Ray(record.point, direction);
		return true;
	}

	double indexOfRefraction;

private:
	static double reflectance(double cosine, double refractionRatio) {
		// Schlick's approximation for reflectance (fresnel factor)
		double r0 = (1 - refractionRatio) / (1 + refractionRatio);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}
};