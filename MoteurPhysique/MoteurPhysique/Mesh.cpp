#include "pch.h"
#include "Mesh.h"
#include "Global.h"
#include <iostream>
#include <fstream>
#include <sstream>


Mesh::Mesh(Vector3 position, Material mat) :
	Object(position, mat)
{
}

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos) pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

Mesh::Mesh(std::string filePath, Vector3 color, float scale, Vector3 pos, Material mat)
{
	material = mat;
	position = pos;
	triangles = std::vector<Triangle*>();
	std::vector<Vector3> v;
	std::vector<Vector3> vn;
	std::vector<std::vector<int>> f;
	std::string s;
	std::string delim = "/";
	// 1) read file data into v, vt, vn and f
	std::ifstream in(filePath, std::ios::in);
	if (!in) { std::cerr << "Cannot open " << filePath << std::endl; exit(1); }
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{ // vertex data
			std::istringstream s(line.substr(2));
			Vector3 v3;
			s >> v3.x; s >> v3.y; s >> v3.z;
			v3.scale(scale);
			v.push_back(v3);
		}
		else if (line.substr(0, 3) == "vn ")
		{ // vertex data
			std::istringstream s(line.substr(3));
			Vector3 v3;
			s >> v3.x; s >> v3.y; s >> v3.z;
			vn.push_back(v3);
		}
		else if (line.substr(0, 2) == "f ")
		{ // vertex data
			std::istringstream s(line.substr(2));
			for (int i = 0; i < 3; i++)
			{
				std::string ss;
				std::vector<int> ff;
				s >> ss;
				std::vector < std::string> sss = split(ss, delim);
				for (int j = 0; j < 3; j++)
				{
					ff.push_back(std::stoi(sss[j]));
				}
				f.push_back(ff);
			}
		}
	}
	// 2) for each face f, store into mesh_data three consecutive vertices in the form:
	// v.x, v.y, v.z, v.w, vt.u, vt.v, vn.x, vn.y, vn.z
	// Caution: obj lists are indexed starting with 1, your vectors with 0 !
	std::vector<Vertex*> vertexs;
	Vector3 normal;
	vertexs.push_back(NULL);
	vertexs.push_back(NULL);
	vertexs.push_back(NULL);
	for (int i = 0; i < f.size() / 3; i++)
	{
		vertexs[0] = new Vertex();
		vertexs[1] = new Vertex();
		vertexs[2] = new Vertex();
		normal = Vector3(0, 0, 0);

		for (int j = 0; j < 3; j++)
		{
			std::vector<int> ff = f[i + j];

			vertexs[j]->position.x = (v[ff[0] - 1].x);
			vertexs[j]->position.y = (v[ff[0] - 1].y);
			vertexs[j]->position.z = (v[ff[0] - 1].z);
			/*mesh_data.push_back(vt[ff[1] - 1].x);
			mesh_data.push_back(vt[ff[1] - 1].y);*/
			if (color.x < 0.0f)
			{
				vertexs[j]->color.x = (abs(vn[ff[2] - 1].x));
				vertexs[j]->color.y = (abs(vn[ff[2] - 1].y));
				vertexs[j]->color.z = (abs(vn[ff[2] - 1].z));
			}
			else
			{
				vertexs[j]->color = color;
			}

			normal = normal + Vector3(vn[ff[2] - 1].x, vn[ff[2] - 1].y, vn[ff[2] - 1].z);
		}
		normal = (normal / 3).normalized();
		triangles.push_back(new Triangle(vertexs[0], vertexs[1], vertexs[2], normal, pos));
	}
}


Mesh::~Mesh()
{
}

float Mesh::rayHit(Vector3 const& rayPos, Vector3 const& rayDir, Vector3& intersecS, Vector3& normalS, Vector3& colorS)
{
	Vector3 intersec;
	Vector3 normal;
	Vector3 color;
	float minDist = 10000000.0f;
	float dist;

	for (int i = 0; i < triangles.size(); i++)
	{
		dist = triangles[i]->rayHit(rayPos, rayDir, intersec, normal, color);
		if (dist < minDist && dist > 0.0f)
		{
			minDist = dist;
			intersecS = intersec;
			normalS = normal;
			colorS = color;
		}
	}

	return minDist;
}

void Mesh::rotateY(float const& delta)
{
	for (Triangle* t : triangles )
	{
		t->rotateY(delta);
	}
}

void Mesh::rotateX(float const& delta)
{
	for (Triangle* t : triangles)
	{
		t->rotateX(delta);
	}
}

void Mesh::rotateZ(float const& delta)
{
	for (Triangle* t : triangles)
	{
		t->rotateZ(delta);
	}
}

void Mesh::rotate(float const& deltaX, float const& deltaY, float const& deltaZ)
{
	for (Triangle* t : triangles)
	{
		t->rotate(deltaX, deltaY, deltaZ);
	}
}

void Mesh::scale(float const& n)
{
	for (Triangle* t : triangles)
		t->scale(n);
}

void Mesh::translate(Vector3 const& v)
{
	position = position + v;
	for (Triangle* t : triangles)
		t->position = position;
}