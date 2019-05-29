#include "pch.h"
#include "Object.h"


Object::Object(Vector3 const& pos, Material const& mat) :
	position(pos), material(mat)
{
}


Object::~Object()
{
}

void Object::translate(Vector3 const& v)
{
	position = position + v;
}