#pragma once
#include <math.h>
#include "cgMath.h"
#include "particlehandler.h"
#include "world.h"
#include "terrain.h"

class sph
{
private:
	float gravity;
	float changeInTime;			// delta t
	float interactionRadius;	// h
	float stiffness;
	float stiffnessNear;
	float restDensity;
	float springConstant;
	float plasticityConstant;	// alpha
	particlehandler* pHandler;
	void doubleDensityRelaxation();
	void springDisplacements();
	void springAdjustment();
	void viscosityImpulses();
	void particleBodyInteractions(terrain*** t);
	triangle triangleAt(vector3 i);
	vector3 collisionImpulse(particle* p, float mew, terrain**** t);
public:
	sph(void);
	sph(particlehandler* p);
	sph(particlehandler* p, float g, float t, float r, float s, float sn, float d, float sk, float pk);
	~sph(void);
	void run(terrain** t);
};
