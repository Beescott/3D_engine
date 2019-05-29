#pragma once
#include "Mesh.h"
class MeshCube : public Mesh
{
public:
	MeshCube(Vector3 position, float r, Material mat);
	~MeshCube();

private:
	float ridge;
};

