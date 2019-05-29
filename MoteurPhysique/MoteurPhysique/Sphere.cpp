#include "pch.h"
#include "Sphere.h"

/**
 * @Brief : Compute the division of two vectors
 * @Return : a new vector with the value of the original vector divided by another
 */
Sphere::Sphere(Vector3 const& pos, Material const& mat, float const& rad, Vector3 const& col) :
	radius(rad), color(col), Object(pos, mat)
{
}


Sphere::~Sphere()
{
}

float Sphere::rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS)
{
	Vector3 diff = rayPos - position;

	float a = rayDir.dot(rayDir);
	float b = 2.0f * diff.dot(rayDir);
	float c = diff.dot(diff) - radius * radius;

	float dist = b * b - 4.0f * a * c;

	if (dist >= 0.0f)
	{
		float sqrtDist = sqrt(dist);
		float den = 1.0f / (2.0f * a);
		float t1 = (-b - sqrtDist) * den;
		float t2 = (-b + sqrtDist) * den;

		if (t1 > 0.0f)
		{
			intersecS = rayPos + rayDir * t1;
			normalS = (intersecS - position).normalized();
			colorS = color;
			return t1;
		}
		if (t2 >= 0.0f)
		{
			intersecS = rayPos + rayDir * t2;
			normalS = (intersecS - position).normalized();
			colorS = color;
			return t1;
		}
	}

	return -1.0f;
}

void Sphere::rotateY(const float& delta)
{
}

void Sphere::rotateX(const float& delta)
{
}

void Sphere::rotateZ(const float& delta)
{
}

void Sphere::rotate(const float& deltaX, const float& deltaY, const float& deltaZ)
{
}

void Sphere::scale(const float& n)
{
	radius *= n;
}