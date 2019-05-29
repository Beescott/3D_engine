#pragma once

#include "Triangle.h"

class Cube : public Object
{
public:
	Cube(Vector3 pos, Vector3 t0, Vector3 t1);
	~Cube();
	float rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS) override;
	void rotateY(const float& delta) override;
	void rotateX(const float& delta) override;
	void rotateZ(const float& delta) override;
	void rotate(const float& deltaX, const float& deltaY, const float& deltaZ) override;
	void scale(const float& n) override;

private:
	Vector3 position;
	Vector3 vMin;
	Vector3 vMax;
	Vector3 color;
};

