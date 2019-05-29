#include "pch.h"
#include "Matrix3.h"

/******************************
*******  CONSTRUCTORS  ********
******************************/

// Initialize a matrix 3x3 of zeros
Matrix3::Matrix3()
{
	buffer = std::vector<Vector3>();
	buffer.push_back(Vector3());
	buffer.push_back(Vector3());
	buffer.push_back(Vector3());
}

// Initialize a matrix 3x3 of Vector3
Matrix3::Matrix3(Vector3 v1, Vector3 v2, Vector3 v3)
{
	buffer = std::vector<Vector3>();
	buffer.push_back(v1);
	buffer.push_back(v2);
	buffer.push_back(v3);
}

// Initialize a matrix 3x3 of Vector3
Matrix3::Matrix3(std::vector<Vector3> vecs)
{
	if (vecs.size() != 3)
		throw std::invalid_argument("Argument must have a size of 3");

	buffer = vecs;
}

// Returns a string containing the value of the matrix
std::string Matrix3::toString()
{
	std::string res = "";
	res += buffer[0].toString() + "\n" + buffer[1].toString() + "\n" + buffer[2].toString();

	return res;
}

//  Get the n-th line
Vector3 Matrix3::getLin(int n) const
{
	return buffer[n];
}

// Get the n-th column
Vector3 Matrix3::getCol(int n)
{
	Vector3 res = Vector3(buffer[0][n], buffer[1][n], buffer[2][n]);
	return res;
}

/******************************
*******   FUNCTIONS    ********
******************************/

Matrix3 Matrix3::operator+(Matrix3 m) const
{
	Matrix3 res = Matrix3(getLin(0) + m.getLin(0),
		getLin(1) + m.getLin(1),
		getLin(2) + m.getLin(2));

	return res;
}

Matrix3 Matrix3::operator-(Matrix3 m) const
{
	Matrix3 res = Matrix3(getLin(0) - m.getLin(0),
		getLin(1) - m.getLin(1),
		getLin(2) - m.getLin(2));

	return res;
}

Matrix3 Matrix3::operator*(Matrix3 m)
{
	Matrix3 res = Matrix3();

	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 3; i++)
			for (int k = 0; k < 3; k++)
				res[j][i] = (*this)[k][i] * m[j][k] + res[j][i];
				//res.set(i, j, get(i, k) * m.get(k, j) + res.get(i,j));

	return res;
}

Matrix3 Matrix3::operator*(float k) const
{
	Matrix3 res = Matrix3(buffer[0] * k, buffer[1] * k, buffer[2] * k);

	return res;
}

Vector3 Matrix3::operator*(Vector3 v)
{
	Vector3 res = Vector3();
	for (int j = 0; j < 3; j++)
	{
		float sum = 0;
		for (int i = 0; i < 3; i++)
			sum += (*this)[j][i] * v[i];
		res[j] = sum;
	}
	return res;
}

Vector3& Matrix3::operator[](int n)
{
	return buffer.at(n);
}

// Return the transposee of a matrix
Matrix3 Matrix3::transposee()
{
	Matrix3 res = Matrix3();
	for (int j = 0; j < 3; j++)
		for (int i = 0; i < 3; i++)
			//res.set(j, i, get(i, j));
			res[i][j] = (*this)[j][i];

	return res;
}

// Rotation of d degrees in the X axis
Matrix3 Matrix3::cardRotX(float d) const
{
	Vector3 p = Vector3(1, 0, 0);
	Vector3 q = Vector3(0, cos(d), sin(d));
	Vector3 r = Vector3(0, -sin(d), cos(d));

	return Matrix3(p, q, r);
}

// Rotation of d degrees in the Y axis
Matrix3 Matrix3::cardRotY(float d) const
{
	Vector3 p = Vector3(cos(d), 0, -sin(d));
	Vector3 q = Vector3(0, 1, 0);
	Vector3 r = Vector3(sin(d), 0, cos(d));

	return Matrix3(p, q, r);
}

// Rotation of d degrees in the Z axis
Matrix3 Matrix3::cardRotZ(float d) const
{
	Vector3 p = Vector3(cos(d), sin(d),  0);
	Vector3 q = Vector3(-sin(d), cos(d), 0);
	Vector3 r = Vector3(0, 0, 1);

	return Matrix3(p, q, r);
}

// Rotation in an arbitrary vector v of d degrees
Matrix3 Matrix3::arbiRot(Vector3 v, float d) const
{ const
	Vector3 p = Vector3(
		v.x * v.x * (1 - cos(d)) + cos(d),
		v.x * v.y * (1 - cos(d)) + v.z * sin(d),
		v.x * v.z * (1 - cos(d)) - v.y * sin(d)
	);

	Vector3 q = Vector3(
		v.x * v.y * (1 - cos(d)) - v.z * sin(d),
		v.y * v.y * (1 - cos(d)) + cos(d),
		v.y * v.z * (1 - cos(d)) + v.x * sin(d)
	);

	Vector3 r = Vector3(
		v.x * v.z * (1 - cos(d)) + v.y * sin(d),
		v.y * v.z * (1 - cos(d)) - v.x * sin(d),
		v.z * v.z * (1 - cos(d)) + cos(d)
	);

	return Matrix3(p, q, r);
}

// Scale the matrix by value k in the vector v direction
Matrix3 Matrix3::scale(Vector3 v, float k) const
{
	Vector3 p = Vector3(
		1 + (k - 1) * v.x * v.x,
		(k - 1) * v.x * v.y,
		(k-1) * v.x * v.z
	);

	Vector3 q = Vector3(
		(k - 1) * v.x * v.y,
		1 + (k - 1) * v.y * v.y,
		(k - 1) * v.y * v.z
	);

	Vector3 r = Vector3(
		(k - 1) * v.x * v.z,
		(k - 1) * v.y * v.z,
		1 + (k - 1) * v.z * v.z
	);

	return Matrix3(p, q, r);
}

// Return the determinant of the matrix
float Matrix3::determinant()
{
	float res = 0.0;
	for (int i = 0; i < 3; i++)
		//res += get(0, i) * get(1, (i + 1) % 3) * get(2, (i + 2) % 3) - get(1, (i + 2) % 3) * get(2, (i + 1) % 3);
		res += (*this)[i][0] * (*this)[(i + 1) % 3][1] * (*this)[(i + 2) % 3][2] - (*this)[(i + 2) % 3][1] * (*this)[(i + 1) % 3][2];
	return res;
}

// Return the inverse of the matrix
Matrix3 Matrix3::inverse()
{
	Matrix3 res = Matrix3();
	for (int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			float cell = (*this)[(i + 1) % 3][(j + 1) % 3] *
				(*this)[(i + 2) % 3][(j + 2) % 3] -
				(*this)[(i + 2) % 3][(j + 1) % 3] *
				(*this)[(i + 1) % 3][(j + 2) % 3];
			res[j][i] = cell;
		}
	return res;
}