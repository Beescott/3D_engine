#pragma once
#include "Vector3.h"

#include <string>

class Vector4 : public Vector3
{
public:
	float w;

	Vector4();
	Vector4(float nx, float ny, float nz, float nw);
	Vector4(std::vector<float> v);
	Vector4(Vector3 v, float w);
	~Vector4();
	std::string toString();

	Vector4 operator+(const Vector4& v);

	void operator=(const Vector4& copy);
};