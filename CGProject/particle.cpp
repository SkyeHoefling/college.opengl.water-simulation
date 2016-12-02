#include "particle.h"
#include "math.h"

particle::particle(void)
{
}

particle::particle(bool isAliv, float lif, float fad)
{
	isAlive = isAliv;
	life = lif;
	fade = fad;

	velocity = vector3(0.0, 0.0, 0.0);
}

particle::~particle(void)
{
}

// getters
bool particle::getIsAlive()	{	return isAlive;	}
float particle::getLife()	{	return life;	}
float particle::getFade()	{	return fade;	}

vector4 particle::getColor()	{	return color;		}

vector3 particle::getPosition()	{	return position;	}
vector3 particle::getVelocity()	{	return velocity;	}
vector3 particle::getGravity()	{	return gravity;		}

float particle::getDensity()	{	return density;		}
float particle::getDensityNear(){	return densityNear;	}
float particle::getPressure()	{	return pressure;	}
float particle::getPressureNear(){	return pressureNear;}
vector3 particle::getPrevPosition()	{	return prevPosition;	}

// setters
void particle::setIsAlive(bool isAliv)	{	isAlive = isAliv;	}
void particle::setLife(float lif)		{	life = lif;			}
void particle::setFade(float fad)		{	fade = fad;			}

void particle::setColor(float r, float g, float b, float a)	
{
	color.setW(r);
	color.setX(b);
	color.setY(g);
	color.setZ(a);
}

void particle::setPosition(vector3 pos)	{	position = pos;		}
void particle::setVelocity(vector3 vel)	{	velocity = vel;		}
void particle::setGravity(vector3 grav)	{	gravity = grav;		}

void particle::setDensity(float dens)			{	density = dens;			}
void particle::setDensityNear(float dNear)		{	densityNear = dNear;	}
void particle::setPressure(float pres)			{	pressure = pres;		}
void particle::setPressureNear(float pres)		{	pressureNear = pres;	}
void particle::setPrevPosition(vector3 prePos)	{	prevPosition = prePos;	}

void particle::setNeighbors(particle *p, int c, int c2)
{
	// vars
	int iter, iter2;
	float min, lastMin, curMin;

	// init the vars
	min = 1000;
	lastMin = 0;

	// set the counts
	neighborsCount = c;
	neighbors = new particle[neighborsCount];
	
	for (iter = 0; iter < neighborsCount; iter++)
	{
		// reset the min
		min = 1000;

		// loop through all particles
		for (iter2 = 0; iter2 < c2; iter2++)
		{
			curMin = getDistance(position, p[iter2].getPosition());

			// if the current min is less than the overall min, and not equal to 0
			if (curMin < min && curMin && curMin > lastMin)
			{
				min = curMin;
				neighbors[iter] = p[iter];
			}
		}

		// set the lastMin
		lastMin = min;
	}
}

float particle::getDistance(vector3 v1, vector3 v2)
{
	float dist;

	// compute the distance
	dist = sqrt(pow(v1.getX() - v2.getX(), 2) + pow(v1.getY() - v2.getY(), 2) + pow(v1.getZ() - v2.getZ(), 2));
	
	// return the distance
	return dist;
}

particle* particle::getNeighbors()	{	return neighbors;		}
int particle::getNeighborsCount()	{	return neighborsCount;	}

bool particle::operator==(particle rhs){
	if(rhs.getColor() == color && rhs.getDensity() == density && rhs.getDensityNear() == densityNear &&
		rhs.getFade() == fade && rhs.getGravity() == gravity && rhs.getIsAlive() == isAlive &&
		rhs.getLife() == life && rhs.getNeighbors() == neighbors && rhs.getNeighborsCount() == neighborsCount &&
		rhs.getPosition() == position && rhs.getPressure() == pressure && 
		rhs.getPressureNear() == pressureNear && rhs.getPrevPosition() == prevPosition && 
		rhs.getVelocity() == velocity) return true;
	return false;
}