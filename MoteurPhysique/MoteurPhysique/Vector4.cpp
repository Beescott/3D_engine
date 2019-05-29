#include "pch.h"
#include "Vector4.h"

/******************************
*******  CONSTRUCTORS  ********
******************************/

Vector4::Vector4() :
	Vector3(), w(0)
{
}

Vector4::~Vector4()
{
}

Vector4::Vector4(float nx, float ny, float nz, float nw) :
	Vector3(nx,ny,nz), w(nw)
{
}

Vector4::Vector4(std::vector<float> v)
{
	if (v.size() != 4)
		throw std::invalid_argument("The vector must have a size of 4");

	x = v.at(0);
	y = v.at(1);
	z = v.at(2);
	w = v.at(3);
}

Vector4::Vector4(Vector3 v, float w) :
	Vector3(v.x, v.y, v.z), w(w)
{
}

/******************************
*******   FUNCTIONS    ********
******************************/

std::string Vector4::toString() 
{
	return Vector3::toString() + " " + std::to_string(w);
}

void Vector4::operator=(const Vector4& copy) 
{
	(*this).x = copy.x;
	(*this).y = copy.y;
	(*this).z = copy.z;
	(*this).w = copy.w;
}

Vector4 Vector4::operator+(const Vector4& v)
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}
