#pragma once
#include <GL/glut.h>
#include <stdio.h>
#include "vector3.h"
#include "triangle.h"

class triangle
{
private:
	vector3 p1;
	vector3 p2;
	vector3 p3;
	vector3 center;
	vector3 normal;
	bool sameSide(vector3 p1, vector3 p2, vector3 a, vector3 b);
public:
	triangle(void);
	triangle(vector3 a, vector3 b, vector3 c);
	~triangle(void);
	vector3 getP1();
	vector3 getP2();
	vector3 getP3();
	vector3 getNormal();
	vector3 calculateNormal();
	vector3 calculateCenter();
	void drawNormal();
	triangle triangleAt(vector3 i);
	bool pointInTri(vector3 i );
};
