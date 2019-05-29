#pragma once
#include "Object.h"

class Sphere :
	public Object
{
public:
	Sphere(Vector3 const& pos = Vector3(0.0f, 0.0f, 0.0f), Material const& mat = Material(), float const& rad = 1.0f, Vector3 const& col = Vector3(1.0f, 1.0f, 1.0f));
	~Sphere();

	float rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS) override;
	void rotateY(const float& delta) override;
	void rotateX(const float& delta) override;
	void rotateZ(const float& delta) override;
	void rotate(const float& deltaX, const float& deltaY, const float& deltaZ) override;
	void scale(const float& n) override;

	float radius;
	Vector3 color;
};

