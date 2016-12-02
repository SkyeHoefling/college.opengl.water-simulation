#pragma once
#include "particle.h"
#include "world.h"
#include "vector3.h"
#include "spring.h"
#include "terrain.h"


class particlehandler
{
public:
	particlehandler(void);
	particlehandler(int max, float speed, world wor);
	~particlehandler(void);
	void init(int t);
	bool generate(int t);
	void display(float s);
	particle *getParticles();
	spring* getSprings();
	int getMax();
	int getSpringCount();
	bool springExist(particle i, particle j);
	spring getSpring(particle i, particle j);
	void addSpring(spring i);
	void removeSpring(spring i);
	bool updateParticles4(terrain* t);
private:
	world w;
	int max;
	int springCount;
	int globalIter;
	bool globalLife;
	float xGrid, yGrid, zGrid;
	float speed;
	particle* particles;
	spring* springs;
	bool initParticles();
	bool generateParticles(int type);
	bool updateParticles();
	bool updateParticles2();
	bool updateParticles3();
	
	bool updateParticles5();
	void drawParticles(float size,bool sphere=false);
};
