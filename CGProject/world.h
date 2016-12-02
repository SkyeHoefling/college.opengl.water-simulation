#pragma once
#include <GL/glut.h>
#include "vector3.h"
class world
{
public:
	world(void);
	world(int w, int l);
	~world(void);
	vector3 getGridPosition(int p);
	vector3* getGrid();
	int getWidth();
	int getLength();
	vector3 getPoint(float x, float z);
	vector3 getSurfaceNormal(vector3 a, vector3 b, vector3 c);
	void getAllNormals();
	void drawNormals();
	void dispaly();
	void setPointAt(int i, float x, float y, float z);
	void setPointAtX(int i, float x);
	void setPointAtY(int i, float y);
	void setPointAtZ(int i, float z);
	bool showNormals;
	void toggleShowNormals();
private:
	vector3* grid;
	int gSize;
	int width;
	int length;
	void initializeGrid();
	vector3* gridNormals;
};
