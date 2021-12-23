#pragma once

class vec3 {
public:
	// Constructors
	vec3() : elems{ 0,0,0 } {}
	vec3(double elem1, double elem2, double elem3) : elems{elem1, elem2, elem3} {}

	// Operator overloads
	vec3 operator-() const { return vec3(-elems[0], -elems[1], -elems[2]); }
	double operator[](int i) const { return elems[i]; }
	double &operator[](int i) { return elems[i]; }

	vec3 &operator+=(const vec3 &vec) {
		elems[0] += vec.elems[0];
		elems[1] += vec.elems[1];
		elems[2] += vec.elems[2];
		return *this;
	}

	vec3 &operator*=(const double t) {
		elems[0] *= t;
		elems[1] *= t;
		elems[2] *= t;
		return *this;
	}

	vec3 &operator /=(const double t) {
		return *this *= 1 / t;
	}

	// Methods
	double length() const {
		return std::sqrt(lengthSquared());
	}

	double lengthSquared() const {
		return elems[0] * elems[0] + elems[1] * elems[1] + elems[2] * elems[2];
	}

	// Members
	double elems[3];
};

// Type aliases
using point3 = vec3;
using color3 = vec3;

// Utility functions

// vector + vector
vec3 operator+(const vec3 &u, const vec3 &v) {
	return vec3(
		u[0] + v[0],
		u[1] + v[1],
		u[2] + v[2]
	);
}

// vector - vector
vec3 operator-(const vec3 &u, const vec3 &v) {
	return vec3(
		u[0] - v[0],
		u[1] - v[1],
		u[2] - v[2]
	);
}

// vector * vector
vec3 operator*(const vec3 &u, const vec3 &v) {
	return vec3(
		u[0] * v[0],
		u[1] * v[1],
		u[2] * v[2]
	);
}

// double * vector
vec3 operator*(double t, const vec3 &vector) {
	return vec3(
		t * vector[0],
		t * vector[1],
		t * vector[2]
	);
}

// vector * double
vec3 operator*(const vec3 &vector, double t) {
	return t * vector;
}

// vector / double
vec3 operator/(vec3 vector, double t) {
	return (1 / t) * vector;
}

double dot(const vec3 &u, const vec3 &v) {
	return 
		u[0] * v[0] + 
		u[1] * v[1] + 
		u[2] * v[2];
}

vec3 cross(const vec3 &u, const vec3 &v) {
	return vec3(
		u[1] * v[2] - u[2] * v[1],
		u[2] * v[0] - u[0] * v[2],
		u[0] * v[1] - u[1] * v[0]
	);
}

vec3 unitVector(vec3 vector) {
	return vector / vector.length();
}