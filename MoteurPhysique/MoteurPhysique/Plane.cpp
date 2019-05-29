#include "pch.h"
#include "Plane.h"


Plane::Plane(Vector3 const& pos, Vector3 const& nor, Material const& mat, Vector3 const& col) :
	Object(pos, mat), normal(nor), color(col)
{
}

Plane::~Plane()
{
}

float Plane::rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS)
{
	normalS = normal.normalized();
	
	Vector3 diff = position - rayPos;
	if (rayDir.dot(normalS) == 0.0f)
		return -1.0f;

	float t = diff.dot(normalS) / rayDir.dot(normalS);
	if (t > 0.0f)
	{
		intersecS = rayPos + rayDir * t;
		colorS = (abs((int)floor((position.x - intersecS.x) / 2.0f) + (int)floor((position.z - intersecS.z) / 2.0f))) % 2 > 0 ? Vector3(1, 1, 1) : Vector3(0.4, 0.4, 0.4);
		return t;
	}
	return -1.0f;
}

void Plane::rotateY(const float& delta)
{
}

void Plane::rotateX(const float& delta)
{
}

void Plane::rotateZ(const float& delta)
{
}

void Plane::rotate(const float& deltaX, const float& deltaY, const float& deltaZ)
{
}

void Plane::scale(const float& n)
{
}