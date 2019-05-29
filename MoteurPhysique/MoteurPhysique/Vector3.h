#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>
#include <math.h>

class Vector3
{
	public:
		float x;
		float y;
		float z;

		Vector3();
		Vector3(float nx, float ny, float nz);
		std::string toString();

		void operator=(const Vector3& copy);
		bool operator==(const Vector3& v) const;
		bool operator!=(const Vector3& v) const;
		Vector3 operator*(const float n) const;
		Vector3 operator*(const Vector3& n) const;
		Vector3 operator/(const float n) const;
		Vector3 operator+(const Vector3& v) const;
		Vector3 operator-(const Vector3& v) const;
		float&  operator[](int n);

		Vector3 neg() const;
		float   mag() const;
		Vector3 normalized() const;
		float   distance(const Vector3& v) const;
		float   dot(const Vector3& v) const;
		Vector3 cross(const Vector3& v) const;

		void rotateX(float const& angle);
		void rotateY(float const& angle);
		void rotateZ(float const& angle);
		void scale(float const& n);
};