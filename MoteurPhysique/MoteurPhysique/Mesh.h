#pragma once

#include "Triangle.h"

class Mesh : public Object
{
public:
	Mesh(Vector3 position, Material mat);
	Mesh(std::string filePath, Vector3 color, float scale, Vector3 pos, Material mat);
	~Mesh();

	float rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS) override;

	void rotateY(float const& delta) override;
	void rotateX(float const& delta) override;
	void rotateZ(float const& delta) override;
	void rotate(float const& deltaX, float const& deltaY, float const& deltaZ) override;
	void scale(float const& n) override;
	void translate(Vector3 const& v) override;

protected:
	std::vector<Triangle*> triangles;
};

