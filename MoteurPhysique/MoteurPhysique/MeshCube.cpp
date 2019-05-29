#include "pch.h"
#include "MeshCube.h"


MeshCube::MeshCube(Vector3 position, float r, Material mat) :
	Mesh(position, mat), ridge(r)
{
	float rd = ridge;
	// Vertex, Vertex, Vertex, Normal, Position
	Vector3 v1 = Vector3(rd, rd, rd);
	Vector3 v2 = Vector3(rd, -rd, rd);
	Vector3 v3 = Vector3(-rd, -rd, rd);
	Vector3 v4 = Vector3(-rd, rd, rd);
	Vector3 v5 = Vector3(-rd, rd, -rd);
	Vector3 v6 = Vector3(-rd, -rd, -rd);
	Vector3 v7 = Vector3(rd, rd, -rd);
	Vector3 v8 = Vector3(rd, -rd, -rd);

	Triangle* t1 = new Triangle(
		new Vertex(v1, Vector3(1, 0, 0)),
		new Vertex(v2, Vector3(0, 1, 0)),
		new Vertex(v3, Vector3(0, 0, 1)),
		Vector3(0,0,1),
		position
	);

	Triangle* t2 = new Triangle(
		new Vertex(v1, Vector3(1, 0, 0)),
		new Vertex(v3, Vector3(0, 0, 1)),
		new Vertex(v4, Vector3(0, 1, 0)),
		Vector3(0, 0, 1),
		position
	);

	Triangle* t3 = new Triangle(
		new Vertex(v4, Vector3(0, 1, 0)),
		new Vertex(v3, Vector3(0, 0, 1)),
		new Vertex(v6, Vector3(0, 1, 0)),
		Vector3(-1, 0, 0),
		Vector3(position)
	);

	Triangle* t4 = new Triangle(
		new Vertex(v4, Vector3(0, 1, 0)),
		new Vertex(v6, Vector3(0, 1, 0)),
		new Vertex(v5, Vector3(1, 0, 0)),
		Vector3(-1, 0, 0),
		Vector3(position)
	);

	Triangle* t5 = new Triangle(
		new Vertex(v5, Vector3(1, 0, 0)),
		new Vertex(v6, Vector3(0, 1, 0)),
		new Vertex(v8, Vector3(0, 0, 1)),
		Vector3(0, 0, -1),
		Vector3(position)
	);

	Triangle* t6 = new Triangle(
		new Vertex(v5, Vector3(1, 0, 0)),
		new Vertex(v8, Vector3(0, 0, 1)),
		new Vertex(v7, Vector3(0, 1, 0)),
		Vector3(0, 0, -1),
		Vector3(position)
	);

	Triangle* t7 = new Triangle(
		new Vertex(v7, Vector3(0, 1, 0)),
		new Vertex(v8, Vector3(0, 0, 1)),
		new Vertex(v2, Vector3(0, 1, 0)),
		Vector3(1, 0, 0),
		Vector3(position)
	);

	Triangle* t8 = new Triangle(
		new Vertex(v7, Vector3(0, 1, 0)),
		new Vertex(v2, Vector3(0, 1, 0)),
		new Vertex(v1, Vector3(1, 0, 0)),
		Vector3(1, 0, 0),
		Vector3(position)
	);

	Triangle* t9 = new Triangle(
		new Vertex(v1, Vector3(1, 0, 0)),
		new Vertex(v4, Vector3(0, 1, 0)),
		new Vertex(v7, Vector3(0, 1, 0)),
		Vector3(0, 1, 0),
		Vector3(position)
	);

	Triangle* t10 = new Triangle(
		new Vertex(v7, Vector3(0, 1, 0)),
		new Vertex(v4, Vector3(0, 1, 0)),
		new Vertex(v5, Vector3(1, 0, 0)),
		Vector3(0, 1, 0),
		Vector3(position)
	);

	Triangle* t11 = new Triangle(
		new Vertex(v3, Vector3(0, 0, 1)),
		new Vertex(v2, Vector3(0, 1, 0)),
		new Vertex(v8, Vector3(0, 0, 1)),
		Vector3(0, -1, 0),
		Vector3(position)
	);

	Triangle* t12 = new Triangle(
		new Vertex(v3, Vector3(0, 0, 1)),
		new Vertex(v8, Vector3(0, 0, 1)),
		new Vertex(v6, Vector3(0, 1, 0)),
		Vector3(0, -1, 0),
		Vector3(position)
	);

	triangles.push_back(t1);
	triangles.push_back(t2);
	triangles.push_back(t3);
	triangles.push_back(t4);
	triangles.push_back(t5);
	triangles.push_back(t6);
	triangles.push_back(t7);
	triangles.push_back(t8);
	triangles.push_back(t9);
	triangles.push_back(t10);
	triangles.push_back(t11);
	triangles.push_back(t12);
}


MeshCube::~MeshCube()
{
}