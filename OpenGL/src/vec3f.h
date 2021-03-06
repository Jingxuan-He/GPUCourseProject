#pragma once
#include <cmath>
#include <ostream>

#include <cuda_runtime.h>
#include <device_launch_parameters.h>

class vec3f {
public:
	union {
		struct {
			float x, y, z;
		};
		struct {
			float v[3];
		};
	};

	__device__ __host__
	__forceinline vec3f()
	{
		x = 0; y = 0; z = 0;
	}

	__device__ __host__
	__forceinline vec3f(const vec3f& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	__device__ __host__
	__forceinline vec3f(const float* v)
	{
		x = v[0];
		y = v[1];
		z = v[2];
	}

	__device__ __host__
	__forceinline vec3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	__device__ __host__
	__forceinline float operator [] (int i) const { return v[i]; }

	__device__ __host__
	__forceinline float& operator [] (int i) { return v[i]; }

	__device__ __host__
	__forceinline vec3f& operator += (const vec3f& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	__device__ __host__
	__forceinline vec3f& operator -= (const vec3f& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	__device__ __host__
	__forceinline vec3f& operator *= (float t) {
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	__device__ __host__
	__forceinline vec3f& operator /= (float t) {
		x /= t;
		y /= t;
		z /= t;
		return *this;
	}

	__device__ __host__
	__forceinline vec3f operator - () const {
		return vec3f(-x, -y, -z);
	}

	__device__ __host__
	__forceinline vec3f operator + (const vec3f& v) const
	{
		return vec3f(x + v.x, y + v.y, z + v.z);
	}

	__device__ __host__
	__forceinline vec3f operator - (const vec3f& v) const
	{
		return vec3f(x - v.x, y - v.y, z - v.z);
	}

	__device__ __host__
	__forceinline vec3f operator * (float t) const
	{
		return vec3f(x * t, y * t, z * t);
	}

	__device__ __host__
	__forceinline vec3f operator / (float t) const
	{
		return vec3f(x / t, y / t, z / t);
	}

	__device__ __host__
	__forceinline const vec3f cross(const vec3f& vec) const
	{
		return vec3f(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
	}

	__device__ __host__
	__forceinline float dot(const vec3f& vec) const {
		return x * vec.x + y * vec.y + z * vec.z;
	}

	__device__ __host__
	__forceinline void normalize()
	{
		float sum = x * x + y * y + z * z;
		if (sum > 1e-6f) {
			float base = float(1.0 / sqrt(sum));
			x *= base;
			y *= base;
			z *= base;
		}
	}

	__device__ __host__
	__forceinline float length() const {
		return float(sqrt(x * x + y * y + z * z));
	}

	__device__ __host__
	__forceinline float squareLength() const {
		return x * x + y * y + z * z;
	}

	__device__ __host__
	static vec3f axis(int n) {
		switch (n) {
			case 0: {
				return xAxis();
			}
			case 1: {
				return yAxis();
			}
			case 2: {
				return zAxis();
			}
		}
		return vec3f();
	}

	__device__ __host__ static vec3f xAxis() { return vec3f(1.f, 0.f, 0.f); }
	__device__ __host__ static vec3f yAxis() { return vec3f(0.f, 1.f, 0.f); }
	__device__ __host__ static vec3f zAxis() { return vec3f(0.f, 0.f, 1.f); }
};

__device__ __host__
inline vec3f operator * (float t, const vec3f& v) {
	return vec3f(v.x * t, v.y * t, v.z * t);
}

__device__ __host__
inline std::ostream& operator << (std::ostream& os, const vec3f& v) {
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
	return os;
}