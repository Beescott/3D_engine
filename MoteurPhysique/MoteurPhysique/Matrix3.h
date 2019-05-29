#pragma once

#include "Vector3.h"
#include <tuple>

class Matrix3 {
	public:
		Matrix3();
		Matrix3(Vector3 v1, Vector3 v2, Vector3 v3);
		Matrix3(std::vector<Vector3> vecs);
		
		std::string toString();
		Vector3 getCol(int n);
		Vector3 getLin(int n) const;
		
		Matrix3 operator+(Matrix3 m) const;
		Matrix3 operator-(Matrix3 m) const;
		Matrix3 operator*(Matrix3 m);
		Matrix3 operator*(float k) const;
		Vector3 operator*(Vector3 v);
		Vector3& operator[](int n);

		Matrix3 transposee();
		Matrix3 cardRotX(float degree) const;
		Matrix3 cardRotY(float degree) const;
		Matrix3 cardRotZ(float degree) const;
		Matrix3 arbiRot(Vector3 v, float degree) const;
		Matrix3 scale(Vector3 v, float k) const;

		float determinant();
		Matrix3 inverse();

	private:
		std::vector<Vector3> buffer;
};