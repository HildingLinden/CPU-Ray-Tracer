#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degresToRadians(double degrees) {
	return degrees * pi / 180.0;
}

class xoroshiro128plus {
	uint64_t rotl(const uint64_t x, int k) {
		return (x << k) | (x >> (64 - k));
	}

	uint64_t s[2];

public:
	xoroshiro128plus() {
		auto seed = std::random_device{};
		s[0] = seed();
		s[1] = seed();
		next();
	}

	double next(void) {
		const uint64_t s0 = s[0];
		uint64_t s1 = s[1];
		const uint64_t result = s0 + s1;

		s1 ^= s0;
		s[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
		s[1] = rotl(s1, 37); // c

		return (result >> 11) * 0x1.0p-53;
	}

	void jump(void) {
		static const uint64_t JUMP[] = { 0xdf900294d8f554a5, 0x170865df4b3201fc };

		uint64_t s0 = 0;
		uint64_t s1 = 0;
		for (int i = 0; i < sizeof JUMP / sizeof * JUMP; i++)
			for (int b = 0; b < 64; b++) {
				if (JUMP[i] & UINT64_C(1) << b) {
					s0 ^= s[0];
					s1 ^= s[1];
				}
				next();
			}

		s[0] = s0;
		s[1] = s1;
	}
};

inline double randomDouble() {
	static xoroshiro128plus rng;
	return rng.next();
}

inline double randomDouble(double min, double max) {
	return randomDouble() * (max - min) + min;
}

#include "ray.h"
#include "vec3.h"