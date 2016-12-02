#pragma once
#include "vector3.h"
#include "vector4.h"

class particle
{
public:
	particle(void);
	particle(bool isAliv, float lif, float fad);
	~particle(void);
	
	void setIsAlive(bool isAliv);
	void setLife(float lif);
	void setFade(float fad);

	void setColor(float r, float b, float g, float a);

	void setPosition(vector3 pos);
	void setVelocity(vector3 vel);
	void setGravity(vector3 grav);

	void setDensity(float dens);
	void setDensityNear(float dNear);
	void setPressure(float pres);
	void setPressureNear(float pres);
	void setPrevPosition(vector3 prePos);
	
	bool getIsAlive();
	float getLife();
	float getFade();

	vector4 getColor();

	vector3 getPosition();
	vector3 getVelocity();
	vector3 getGravity();

	float getDensity();
	float getDensityNear();
	float getPressure();
	float getPressureNear();
	vector3 getPrevPosition();

	void setNeighbors(particle* p, int c, int c2);
	particle* getNeighbors();
	int getNeighborsCount();
	float getDistance(vector3 v1, vector3 v2);

	bool operator==(particle rhs);
private:
	bool isAlive;
	float life;
	float fade;

	vector4 color;

	vector3 position;
	vector3 velocity;
	vector3 gravity;

	float density;
	float densityNear;
	float pressure;
	float pressureNear;
	vector3 prevPosition;

	particle* neighbors;
	int neighborsCount;
};
