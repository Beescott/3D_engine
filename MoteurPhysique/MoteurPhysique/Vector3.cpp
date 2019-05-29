#include "pch.h"
#include "Vector3.h"

/******************************
*******  CONSTRUCTORS  ********
******************************/

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float nx, float ny, float nz)
{
	x = nx;
	y = ny;
	z = nz;
}

/******************************
*******   FUNCTIONS    ********
******************************/


// Display the values of the vector
std::string Vector3::toString()
{
	//std::cout << x << " " << y << " " << z << " " << std::endl;
	return std::to_string(x) + " " + 
		   std::to_string(y) + " " + 
		   std::to_string(z);
}

/**
 * Operators surcharge
 */

void Vector3::operator=(const Vector3& copy)
{
	x = copy.x;
	y = copy.y;
	z = copy.z;
}

bool Vector3::operator==(const Vector3& v) const
{
	return x == v.x &&
		y == v.y &&
		z == v.z;
}

bool Vector3::operator!=(const Vector3& v) const
{
	return !(*this == v);
}

// Return a new vector with the negated value of the original vector
Vector3 Vector3::neg() const
{
	Vector3 newVec(-x, -y, -z);
	return newVec;
}

// Return a float corresponding to the magnitude of the vector
float Vector3::mag() const
{
	return sqrt(x * x + y * y + z * z);
}

/**
 * @Brief : Compute the multiplication of two vectors
 * @Return : a new vector with the value of the original vector multiplied with an other
 */
Vector3 Vector3::operator*(const float n) const
{
	Vector3 newVec(x*n, y*n, z*n);
	return newVec;
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);;
}

/**
 * @Brief : Compute the division of two vectors
 * @Return : a new vector with the value of the original vector divided by another
 */
Vector3 Vector3::operator/(const float n) const
{
	if (n == 0)
		throw std::invalid_argument("Can't divide by 0");

	Vector3 newVec(x/n, y/n, z/n);
	return newVec;
}

/**
 * @Brief : Normalization of a vector
 * @Return : a normalized vector
 */
Vector3 Vector3::normalized() const
{
	return (*this / mag());
}

/**
 * @Brief : Compute the addition of two vectors
 * @Return : a new vector with the value of the addition of the original vector and another one
 */
Vector3 Vector3::operator+(const Vector3& v) const
{
	Vector3 newVec = Vector3(x + v.x, y + v.y, z + v.z);
	return  newVec;
}

/**
 * @Brief : Compute the difference of two vectors
 * @Return : a new vector with the value of the difference of the original vector and another one
 */
Vector3 Vector3::operator-(const Vector3& v) const
{
	Vector3 newVec = Vector3(x - v.x, y - v.y, z - v.z);
	return newVec;
}

float& Vector3::operator[](int n)
{
	if (n == 0)
		return x;
	if (n == 1)
		return y;
	if (n == 2)
		return z;
}

// Return the distance to v
float Vector3::distance(const Vector3& v) const
{
	Vector3 newVec(v.x - x, v.y - y, v.z - z);
	return newVec.mag();
}

// Return the dot product of this with v
float Vector3::dot(const Vector3& v) const
{
	return v.x * x + v.y * y + v.z * z;
}

// Return the cross product of this with v
Vector3 Vector3::cross(const Vector3& v) const
{
	Vector3 newVec(y*v.z - z*v.y,
		z*v.x - x*v.z,
		x*v.y - y*v.x);

	return newVec;
}

void Vector3::rotateX(float const& angle) 
{
	float y1 = y * cos(angle) - z * sin(angle);
	float z1 = y * sin(angle) + z * cos(angle);
	y = y1;
	z = z1;
}

void Vector3::rotateY(float const& angle)
{
	float x1 = x * cos(angle) + z * sin(angle);
	float z1 = -x * sin(angle) + z * cos(angle);
	x = x1;
	z = z1;
}

void Vector3::rotateZ(float const& angle)
{
	float x1 = x * cos(angle) - y * sin(angle);
	float y1 = x * sin(angle) + y * cos(angle);
	x = x1;
	y = y1;
}

void Vector3::scale(float const& n)
{
	x *= n;
	y *= n;
	z *= n;
}