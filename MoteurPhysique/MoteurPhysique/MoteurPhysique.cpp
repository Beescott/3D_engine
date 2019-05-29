// MoteurPhysique.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "Vector3.h"
#include "Vector4.h"
#include "Triangle.h"
#include "Matrix3.h"
#include "MeshCube.h"
#include "Plane.h"
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Sphere.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#define SCREEN_X 320
#define SCREEN_Y 180
#define TITLE "Maths3D"
#define FARVIEW 300.0f

float degreeToRadian(float d);

const float cameraFovY = degreeToRadian(80.0f);

bool ortho = false;
int selectedObject = -1;

Vector3 rayPos;
Vector3 rayDir;
Vector3 intersecS;
Vector3 normalS;
Vector3 colorS;
Material materialS;
Vector3 cameraPos = Vector3(0, 0, 5);
Vector3 cameraDirection = Vector3(0, 0, -1);
Vector3 cameraDirectionBase = cameraDirection;
float rotationJX = 0.0f;
float rotationJY = 0.0f;
float vitesseJ = 0.36f;
float scaleUp = 1.1f;
float scaleDown = 0.9f;

bool xPressed = false;
bool yPressed = false;
bool zPressed = false;
bool rPressed = false;

bool wPressed = false;
bool aPressed = false;
bool sPressed = false;
bool dPressed = false;

bool complexMeshShown = true;

std::vector<int> complexObjectsIds;

float scaleSphere = 1.0f;

float degreeToRadian(float d)
{
	return d * (float)M_PI / 180.0f;
}

Vector3 ambiantCol = Vector3(0.0f, 0.0f, 1.0f);
Vector3 lightCol = Vector3(1, 1, 1);
Vector3 lightPos = Vector3(8, 10, 12);

std::vector<Object*> objects = std::vector<Object*>();

Vector3 leftClick;
Vector3 rightClick;
Vector3 middleClick;
bool leftClicking = false;
bool rightClicking = false;
bool middleClicking = false;

int nbFrame = 0;
int timebase = 0;

void initObjects()
{
	Material sphereMat = { 0.2f, 0.7f, 1.0f, 50.0f };
	Object* object = new Sphere(Vector3(5, 0, 0), sphereMat, 1.0f, Vector3(1.0f, 0.0f, 0.0f));
	objects.push_back(object);

	Material triangleMat = { 0.2f, 0.7f, 1.0f, 50.0f };
	object = new Triangle(new Vertex(Vector3(3, 0, 0), Vector3(1, 0, 0)), new Vertex(Vector3(-3, 0, 0), Vector3(0, 1, 0)), new Vertex(Vector3(0, 3, 0), Vector3(0, 0, 1)), Vector3(0, 0, 1), Vector3(0, 0, 0), triangleMat);
	objects.push_back(object);

	Material meshCubeMat = { 0.2f, 0.7f, 1.0f, 50.0f };
	object = new MeshCube(Vector3(5, 0, 0), 0.8f, meshCubeMat);
	objects.push_back(object);

	object = new MeshCube(Vector3(5, 3, 0), 0.8f, meshCubeMat);
	objects.push_back(object);

	Material planeMat = {0.2f, 1.0f, 0.2f, 5.0f};
	object = new Plane(Vector3(0,-2,0), Vector3(0,0.1f,0), planeMat, Vector3(1,1,1));
	objects.push_back(object);

	Material complexMat = { 0.2f, 1.0f, 0.2f, 5.0f };
	object = new Mesh("Objs/book.obj", Vector3(-1.0, 0.0, 0.0), 10.0f, Vector3(-5, 0, 0), complexMat);
	objects.push_back(object); complexObjectsIds.push_back(objects.size()-1);
}

void moveJ(Vector3 v)
{
	Vector3 moveToDroit = Vector3(cameraDirection.x, 0, cameraDirection.z);

	Vector3 ret = moveToDroit * v.z;
	moveToDroit.rotateY(M_PI / 2.0f);
	ret = ret + moveToDroit * v.x;

	cameraPos = cameraPos + ret;
}

void movePlayer()
{
	if (wPressed)
		moveJ(Vector3(0, 0, vitesseJ));
	if (dPressed)
		moveJ(Vector3(vitesseJ, 0, 0));
	if (sPressed)
		moveJ(Vector3(0, 0, -vitesseJ));
	if (aPressed)
		moveJ(Vector3(-vitesseJ, 0, 0));
}

float max(float a, float b)
{
	return a > b ? a : b;
}

void computeCameraRayFromPixel(int px, int py)
{
	float focal = 1.0f / tan(cameraFovY / 2.0f);

	if (ortho)
	{
		Vector3 cz = cameraDirection.normalized(); // enlever normalized lorsqu'on est sûr que la cameraDirection est normalisée.
											 //Vector3 cz = (cameraDirection - cameraPos).normalized();
		Vector3 lessUp = Vector3(0.0f, -1.0f, 0.0f);
		Vector3 cx = lessUp.cross(cz);
		Vector3 cy = cz.cross(cx);

		Vector3 pt = Vector3(((float)(2.0f * px - SCREEN_X)) / SCREEN_Y, ((float)(2.0f * py - SCREEN_Y)) / SCREEN_Y, 0.0f);

		rayPos = cameraPos + (cx.neg() * pt.x - cy * pt.y);
		rayDir = cz;
	}
	else
	{
		Vector3 cz = cameraDirection.normalized(); // enlever normalized lorsqu'on est sûr que la cameraDirection est normalisée.
	//Vector3 cz = (cameraDirection - cameraPos).normalized();
		Vector3 lessUp = Vector3(0.0f, -1.0f, 0.0f);
		Vector3 cx = lessUp.cross(cz);
		Vector3 cy = cz.cross(cx);

		Vector3 pt = Vector3(((float)(2.0f * px - SCREEN_X)) / SCREEN_Y, ((float)(2.0f * py - SCREEN_Y)) / SCREEN_Y, 0.0f);

		rayPos = cameraPos;
		rayDir = (cx.neg() * pt.x - cy * pt.y + cz * focal).normalized();
	}
}

Vector3 computePhongShading(Vector3 const& color, Material const& material, Vector3 const& normalS, Vector3 const& L, Vector3 const& R, Vector3 const& V)
{
	float facing = normalS.dot(L) > 0.0f ? 1.0f : 0.0f;
	Vector3 ambiant = ambiantCol * material.Ka;
	Vector3 diffuse = (lightCol * color) * (material.Kd * max(normalS.dot(L), 0.0f));
	Vector3 specular = lightCol * (material.Ks * facing * pow(max(R.dot(V), 0.0f), material.Kn));

	return (ambiant + diffuse + specular);
}

Vector3 getPixel(int px, int py, bool& hit)
{
	computeCameraRayFromPixel(px, py);

	Vector3 intersec;
	Vector3 normal;
	Vector3 color;
	float minDist = 10000000.0f;
	float dist;
	int id;
	bool show = true;

	for (int i = 0; i < objects.size(); i++)
	{
		if (!complexMeshShown)
		{
			show = true;
			for (int j = 0; j < complexObjectsIds.size(); j++)
			{
				if (i == complexObjectsIds[j])
					show = false;
			}
		}
		if (show)
		{
			dist = objects[i]->rayHit(rayPos, rayDir, intersec, normal, color);

			if (dist < minDist && dist > 0.0f)
			{
				minDist = dist;
				intersecS = intersec;
				normalS = normal;
				colorS = color;
				materialS = objects[i]->material;
				id = i;
			}
		}
	}

	if (minDist > 0.0f && minDist < FARVIEW)
	{
		Vector3 L = (lightPos - intersecS).normalized();
		Vector3 R = (normalS * (normalS.dot(L) * 2.0f) - L);
		Vector3 V = rayDir.neg().normalized();

		hit = true;

		if (id == selectedObject)
			colorS = colorS + Vector3(0.3f, 0.3f, 0.45f);

		color = computePhongShading(colorS, materialS, normalS, L, R, V);
	}
	else
	{
		hit = false;
		color = Vector3(0, 0, 0);
	}
	return color;
}

int getObject(int px, int py, bool& hit)
{
	computeCameraRayFromPixel(px, py);

	Vector3 intersec;
	Vector3 normal;
	Vector3 color;
	float minDist = 10000000.0f;
	float dist;
	int idObject = -1;

	for (int i = 0; i < objects.size(); i++)
	{
		dist = objects[i]->rayHit(rayPos, rayDir, intersec, normal, color);
		if (dist < minDist && dist > 0.0f)
		{
			minDist = dist;
			intersecS = intersec;
			normalS = normal;
			colorS = color;
			materialS = objects[i]->material;
			idObject = i;
		}
	}

	if (minDist > 0.0f && minDist < FARVIEW)
	{
		hit = true;
	}
	else
	{
		hit = false;
		idObject = -1;
	}
	return idObject;
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	bool hit;

	objects[2]->rotate(0.005f, 0.005f, 0.005f);
	movePlayer();

	glBegin(GL_POINTS);

	for (int i = 0; i < SCREEN_X; i++)
	{
		for (int j = 0; j < SCREEN_Y; j++)
		{
			Vector3 c = getPixel(i, j, hit);
			if (hit)
			{ 
				glColor3f(c.x, c.y, c.z);
				glVertex2i(2*i, 2*j);
				glVertex2i(2 * i + 1, 2 * j);
				glVertex2i(2 * i, 2 * j + 1);
				glVertex2i(2 * i + 1, 2 * j + 1);
			}
		}
	}
		
	glEnd();

	glutSwapBuffers();
}

void initGlut() 
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(2*SCREEN_X, 2*SCREEN_Y); //optional
	glutCreateWindow("OpenGL First Window");
}

void init()
{
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 2*SCREEN_X, 0.0f, 2*SCREEN_Y, -2.0, 2.0);
	glViewport(0, 0, 2*SCREEN_X, 2*SCREEN_Y);

}

void idlefunc()
{
	nbFrame++;
	//std::cout << nbFrame << std::endl;
	int time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		int fps = nbFrame * (1000.0 / (float)(time - timebase));

		//std::cout << "nb Frame : " << nbFrame << " - fps : " << fps << " - time - time base : " << time - timebase << std::endl;
		timebase = time;
		nbFrame = 0;

		std::string s = TITLE;
		s += " - ";
		s += std::to_string(fps);
		s += " fps";

		const char *c = s.data();

		glutSetWindowTitle(c);


	}

	glutPostRedisplay();
}

void keyfunc(unsigned char key, int x, int y)
{
	if (key == 'w')
		wPressed = true;
	if (key == 'd')
		dPressed = true;
	if (key == 's')
		sPressed = true;
	if (key == 'a')
		aPressed = true;

	if (key == 'p')
		ortho = !ortho;

	if (key == 'x')
		xPressed = true;
	if (key == 'y')
		yPressed = true;
	if (key == 'z')
		zPressed = true;
	if (key == 'r')
		rPressed = true;

	if (key == 'm')
		complexMeshShown = !complexMeshShown;

	if (selectedObject != -1)
	{
		if (key == '+')
		{
			if (xPressed || yPressed || zPressed) // rotation / position
			{
				if (rPressed) // rotation
					objects[selectedObject]->rotate((xPressed) ? 0.05f : 0.0f, (yPressed) ? 0.05f : 0.0f, (zPressed) ? 0.05f : 0.0f);
				else
					objects[selectedObject]->translate(Vector3((xPressed) ? 0.1f : 0.0f, (yPressed) ? 0.1f : 0.0f, (zPressed) ? 0.1f : 0.0f));
			}
			else // scale
				objects[selectedObject]->scale(scaleUp);
		}
				
		if (key == '-')
		{
			if (xPressed || yPressed || zPressed) // rotation / position
			{
				if (rPressed) // rotation
					objects[selectedObject]->rotate((xPressed) ? -0.05f : 0.0f, (yPressed) ? -0.05f : 0.0f, (zPressed) ? -0.05f : 0.0f);
				else
					objects[selectedObject]->translate(Vector3((xPressed) ? -0.1f : 0.0f, (yPressed) ? -0.1f : 0.0f, (zPressed) ? -0.1f : 0.0f));
			}
			else
				objects[selectedObject]->scale(scaleDown);
		}
	}

}

void keyupfunc(unsigned char key, int x, int y)
{
	if (key == 'w')
		wPressed = false;
	if (key == 'd')
		dPressed = false;
	if (key == 's')
		sPressed = false;
	if (key == 'a')
		aPressed = false;

	if (key == 'x')
		xPressed = false;
	if (key == 'y')
		yPressed = false;
	if (key == 'z')
		zPressed = false;
	if (key == 'r')
		rPressed = false;
}

void mousefunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		leftClick.x = (float)x;
		leftClick.y = (float)y;
		leftClicking = true;

		bool hit;
		selectedObject = getObject(x, SCREEN_Y-y, hit);
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		leftClicking = false;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		rightClick.x = (float)x;
		rightClick.y = (float)y;
		rightClicking = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		rightClicking = false;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		middleClick.x = (float)x;
		middleClick.y = (float)y;
		middleClicking = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		middleClicking = false;
	}
}

void motionfunc(int x, int y)
{
	if (leftClicking && (leftClick.x != x || leftClick.y != y))
	{


		leftClick.x = x;
		leftClick.y = y;
	}

	if (rightClicking && (rightClick.x != x || rightClick.y != y))
	{
		float xx = -((float)(rightClick.x - x)) / 300.0f;
		float yy = ((float)(rightClick.y - y)) / 300.0f;

		rotationJX += yy;
		if (rotationJX <= -M_PI / 2.0f || rotationJX >= M_PI / 2.0f)
			rotationJX -= yy;
		rotationJY += xx;

		cameraDirection = cameraDirectionBase;
		cameraDirection.rotateX(rotationJX);
		cameraDirection.rotateY(rotationJY);
		
		rightClick.x = x;
		rightClick.y = y;
	}

	if (middleClicking && (middleClick.x != x || middleClick.y != y))
	{


		middleClick.x = x;
		middleClick.y = y;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	initGlut();
	init();
	initObjects();

	glutDisplayFunc(render);
	glutKeyboardFunc(keyfunc);
	glutKeyboardUpFunc(keyupfunc);
	glutMouseFunc(mousefunc);
	glutMotionFunc(motionfunc);
	glutIdleFunc(idlefunc);

	glutMainLoop();

	for (int i = 0; i < objects.size(); i++)
	{
		free(objects[i]);
	}
	objects.clear();

	return 0;
}