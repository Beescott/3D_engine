#include "pch.h"
#include "Triangle.h"

#define EPSILON 0.0000001f

//Triangle::Triangle(Vertex v[3], Vector3 nor, Vector3 const& pos, Material const& mat) :
//	Object(pos, mat), normal(nor)
//{
//	vertexs[0] = v[0];
//	vertexs[1] = v[1];
//	vertexs[2] = v[2];
//}

Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3, Vector3 nor, Vector3 const& pos, Material const& mat) :
	Object(pos, mat), normal(nor)
{
	vertexs.push_back(v1);
	vertexs.push_back(v2);
	vertexs.push_back(v3);
}

Triangle::~Triangle()
{
}

float Triangle::rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS)
{
	Vector3 edge1, edge2, h, s, q;
	float a, f, u, v;
	
	edge1 = vertexs[1]->position - vertexs[0]->position;
	edge2 = vertexs[2]->position - vertexs[0]->position;

	h = rayDir.cross(edge2);
	a = edge1.dot(h);

	if (a > -EPSILON && a < EPSILON)
		return -1.0f;
	f = 1.0f / a;
	s = rayPos - (vertexs[0]->position + position);
	u = f * (s.dot(h));
	
	if (u < 0.0f || u > 1.0f)
		return -1.0f;

	q = s.cross(edge1);
	v = f * rayDir.dot(q);

	if (v < 0.0f || u + v > 1.0f)
		return -1.0f;

	float t = f * edge2.dot(q);
	if (t > EPSILON)
	{
		normalS = normal;
		intersecS = rayPos + rayDir * t;

		float d1 = intersecS.distance(vertexs[0]->position + position);
		float d2 = intersecS.distance(vertexs[1]->position + position);
		float d3 = intersecS.distance(vertexs[2]->position + position);
		if (d1 == 0.0f)
			colorS = vertexs[0]->color;
		else if (d2 == 0.0f)
			colorS = vertexs[1]->color;
		else if (d3 == 0.0f)
			colorS = vertexs[2]->color;
		else
		{
			float w1 = 1.0f / d1;
			float w2 = 1.0f / d2;
			float w3 = 1.0f / d3;
			colorS = (vertexs[0]->color * w1 + vertexs[1]->color * w2 + vertexs[2]->color * w3) / (w1 + w2 + w3);
		}
		return t;
	}

	return -1.0f;
}

void Triangle::rotateY(const float& delta)
{
	for (int i = 0; i < 3; i++)
	{
		vertexs[i]->position.rotateY(delta);
	}
	normal.rotateY(delta);
}

void Triangle::rotateX(const float& delta)
{
	for (int i = 0; i < 3; i++)
	{
		vertexs[i]->position.rotateX(delta);
	}
	normal.rotateX(delta);
}

void Triangle::rotateZ(const float& delta)
{
	for (int i = 0; i < 3; i++)
	{
		vertexs[i]->position.rotateZ(delta);
	}
	normal.rotateZ(delta);
}

void Triangle::rotate(const float& deltaX, const float& deltaY, const float& deltaZ)
{
	rotateZ(deltaZ);
	rotateX(deltaX);
	rotateY(deltaY);
}

void Triangle::scale(const float& n)
{
	for (Vertex* v : vertexs)
	{
		v->position = v->position * n;
	}
}