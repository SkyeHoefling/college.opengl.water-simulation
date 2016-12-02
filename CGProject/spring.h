#pragma once
#include "particle.h"

class spring
{
private:
	particle start;
	particle end;
	float distance;
	float restLength;
public:
	spring(void);
	spring(particle s, particle e);
	~spring(void);
	particle getStart();
	particle getEnd();
	float getDistance();
	float getRestLength();
	void setRestLength(float i);
};
