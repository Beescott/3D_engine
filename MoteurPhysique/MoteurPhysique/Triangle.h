#pragma once
#include "Vertex.h"
#include "Object.h"

#include <vector>

class Triangle : public Object
{
	public:
		Triangle(Vertex* v1, Vertex* v2, Vertex* v3, Vector3 nor, Vector3 const& pos = Vector3(0.0f, 0.0f, 0.0f), Material const& mat = Material());
		~Triangle();
		float rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS) override;
		void rotateY(const float& delta) override;
		void rotateX(const float& delta) override;
		void rotateZ(const float& delta) override;
		void rotate(const float& deltaX, const float& deltaY, const float& deltaZ) override;
		void scale(const float& n) override;

		std::vector<Vertex*> vertexs;
		Vector3 normal;
};

