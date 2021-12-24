#pragma once

class Vec3 {
public:
	// Constructors
	Vec3() : elems{ 0,0,0 } {}
	Vec3(double elem1, double elem2, double elem3) : elems{elem1, elem2, elem3} {}

	// Operator overloads
	Vec3 operator-() const { return Vec3(-elems[0], -elems[1], -elems[2]); }
	double operator[](int i) const { return elems[i]; }
	double &operator[](int i) { return elems[i]; }

	Vec3 &operator+=(const Vec3 &vec) {
		elems[0] += vec.elems[0];
		elems[1] += vec.elems[1];
		elems[2] += vec.elems[2];
		return *this;
	}

	Vec3 &operator*=(const double t) {
		elems[0] *= t;
		elems[1] *= t;
		elems[2] *= t;
		return *this;
	}

	Vec3 &operator /=(const double t) {
		return *this *= 1 / t;
	}

	// Methods
	double length() const {
		return std::sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return elems[0] * elems[0] + elems[1] * elems[1] + elems[2] * elems[2];
	}

	static Vec3 random() {
		return Vec3(randomDouble(), randomDouble(), randomDouble());
	}

	static Vec3 random(double min, double max) {
		return Vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
	}

	// Members
	double elems[3];
};

// Type aliases
using Point3 = Vec3;
using Color3 = Vec3;

// Utility functions

// vector + vector
Vec3 operator+(const Vec3 &u, const Vec3 &v) {
	return Vec3(
		u[0] + v[0],
		u[1] + v[1],
		u[2] + v[2]
	);
}

// vector - vector
Vec3 operator-(const Vec3 &u, const Vec3 &v) {
	return Vec3(
		u[0] - v[0],
		u[1] - v[1],
		u[2] - v[2]
	);
}

// vector * vector
Vec3 operator*(const Vec3 &u, const Vec3 &v) {
	return Vec3(
		u[0] * v[0],
		u[1] * v[1],
		u[2] * v[2]
	);
}

// double * vector
Vec3 operator*(double t, const Vec3 &vector) {
	return Vec3(
		t * vector[0],
		t * vector[1],
		t * vector[2]
	);
}

// vector * double
Vec3 operator*(const Vec3 &vector, double t) {
	return t * vector;
}

// vector / double
Vec3 operator/(Vec3 vector, double t) {
	return (1 / t) * vector;
}

double dot(const Vec3 &u, const Vec3 &v) {
	return 
		u[0] * v[0] + 
		u[1] * v[1] + 
		u[2] * v[2];
}

Vec3 cross(const Vec3 &u, const Vec3 &v) {
	return Vec3(
		u[1] * v[2] - u[2] * v[1],
		u[2] * v[0] - u[0] * v[2],
		u[0] * v[1] - u[1] * v[0]
	);
}

Vec3 unitVector(Vec3 vector) {
	return vector / vector.length();
}

Vec3 randomPointInUnitSphere() {
	// Keep picking points in the unit cube until one is found inside the unit sphere
	while (true) {
		Vec3 point = Vec3::random(-1, 1);
		if (point.lengthSquared() < 1) {
			return point;
		}
	}
}

Vec3 randomPointOnUnitSphere() {
	return unitVector(randomPointInUnitSphere());
}