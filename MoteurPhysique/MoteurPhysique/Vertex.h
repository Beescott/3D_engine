#pragma once

#include "Vector3.h"

class Vertex
{
public:
	Vertex(Vector3 pos = Vector3(0, 0, 0), Vector3 col = Vector3(0, 0, 0));
	~Vertex();
	Vector3 position;
	Vector3 color;
};