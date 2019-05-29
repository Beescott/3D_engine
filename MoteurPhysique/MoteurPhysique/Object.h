#pragma once

#include "Vector3.h"
#include "Global.h"

class Object
{
	public:
		Object(Vector3 const& pos = Vector3(0.0f, 0.0f, 0.0f), Material const& mat = Material());
		~Object();

		virtual float rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS) = 0;
		virtual void rotateY(float const& delta) = 0;
		virtual void rotateX(float const& delta) = 0;
		virtual void rotateZ(float const& delta) = 0;
		virtual void rotate(float const& deltaX, float const& deltaY, float const& deltaZ) = 0;
		virtual void scale(float const& n) = 0;
		virtual void translate(Vector3 const& v);

		Vector3 position;
		Material material;
};

