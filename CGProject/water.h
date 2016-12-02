#pragma once
#include "particle.h"
#include <GL/glut.h>
#include "world.h"

class water
{
private:
	bool waves;
	particle* particles;
	int pMax;
	int iterator;
	bool alive;
public:
	water(void);
	~water(void);
	void display(float size);
	void update(world w);
	void generate(int waterHeight, int waterFloor, int xBound, int yBound);
	void toggleWaves();
	bool isAlive();
	int getPMax();
	particle* getParticles();
};
