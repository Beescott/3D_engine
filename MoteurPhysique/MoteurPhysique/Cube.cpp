#include "pch.h"
#include "Cube.h"


Cube::Cube(Vector3 pos, Vector3 v0, Vector3 v1) :
	position(pos), vMin(v0), vMax(v1)
{

}


Cube::~Cube()
{
}

float min(const float& a, const float& b)
{
	return a < b ? a : b;
}

float max(const float& a, const float& b)
{
	return a > b ? a : b;
}

float Cube::rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS)
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	float u = -2.0f;
	float v = 0.0f;
	float w = u * v;

	float divX = 0.0f;
	float divY = 0.0f;
	float divZ = 0.0f;

	// on x
	if (rayDir.x != 0.0f)
		divX = 1 / rayDir.x;

	if (divX >= 0) 
	{
		tmin = vMin.x - rayPos.x * divX;
		tmax = vMax.x - rayPos.x * divX;
	}
	else
	{
		tmin = vMax.x - rayPos.x * divX;
		tmax = vMax.x - rayPos.x * divX;
	}

	// on y
	if (rayDir.y != 0.0f)
		divY = 1 / rayDir.y;

	if (divY >= 0)
	{
		tmin = vMin.y - rayPos.y * divY;
		tymax = vMax.y - rayPos.y * divY;
	}
	else
	{
		tmin = vMax.y - rayPos.y * divY;
		tymax = vMin.y - rayPos.y * divY;
	}

	if (rayDir.z != 0.0f)
		divZ = 1 / rayDir.z;

	if (tmin > tymax || tymin > tmax)
		return -1.0f;
	tmin = min(tmin, tymin);
	tmax = max(tmax, tymax);

	if (rayDir.z >= 0.0f)
	{
		tzmin = vMin.z - rayPos.z / rayDir.z;
		tzmax = vMax.z - rayPos.z / rayDir.z;
	}
	else
	{
		tzmin = vMax.z - rayPos.z / rayDir.z;
		tzmax = vMin.z - rayPos.z / rayDir.z;
	}

	if (tmin > tzmax || tzmin > tmax)
		return -1.0f;

	tmin = min(tmin, tzmin);
	tmax = max(tzmax, tmax);
	
	if (tmin > 0)
		return tmin;
	else
		return tmax;
}

void Cube::rotateY(float const& delta)
{
}

void Cube::rotateX(float const& delta)
{
}

void Cube::rotateZ(float const& delta)
{
}

void Cube::rotate(float const& deltaX, float const& deltaY, float const& deltaZ)
{
}

void Cube::scale(float const& n)
{

}