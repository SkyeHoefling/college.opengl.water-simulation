#pragma once
#include <math.h>
#include "quaternion.h"
#include "vector3.h"

class camera
{
public:
	float const *r, *u, *f;
	float *p;
private:
	float t[16];
public:
	camera(float x=0.0f, float y=0.0f, float z=0.0f);
	~camera();	
	void translateCam(float x, float y, float z, float d = 1.0f);
	void translateWorld(float x, float y, float z, float d = 1.0f);
	void rotateCam(float angle, float x, float y, float z);
	void rotateWorld(float angle, float x, float y, float z);
private:
	void setView();
/*public:
	camera(void);	
	~camera(void);
	float angle;
	void translate(float x, float y, float z);
	void rotate(float theta, float x, float y, float z);
	void setView();
	void init();
	void init(int w, int h);
private:
	void update();
	quaternion view;
	vector3 position;
	vector3 up;*/
};
