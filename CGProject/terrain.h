#pragma once
#include <GL/glut.h>
#include "world.h"
#include "triangle.h"

class terrain
{
public:
	terrain(void);
	terrain(world wor);
	~terrain(void);
	void display();
	void generate(int iterations, int gridWidth, int gridLength, float maxHeight);
	void smooth(int iterations, int gridWidth, int gridLength, float k);
	bool toggleNormals();
	triangle getTri(vector3* i);
private:
	triangle* tris;
	world w;
	bool particleDeposition(int iterations, int gridWidth, int gridLength, float maxHeight);
	bool smoothTerrain(int iterations, int gridWidth, int gridLength, float h);
	bool drawNormals;
};
