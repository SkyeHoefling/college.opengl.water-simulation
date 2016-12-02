#include "particlehandler.h"
#include "math.h"
#include <stdlib.h>
#include <GL/glut.h>
#include "sph.h"
sph s;
particlehandler::particlehandler(void)
{
}

particlehandler::particlehandler(int mx, float spd, world wor)
{
	max = mx;
	speed = spd;
	particles = new particle[max];
	w = wor;
}
particlehandler::~particlehandler(void)
{
}

void particlehandler::init(int t)
{
	initParticles();
	generateParticles(t);
}

bool particlehandler::generate(int t)
{
	bool hasLife;
	if (t == 0)
	{
		hasLife = updateParticles();
	}
	else if (t == 1)
	{
		hasLife = updateParticles2();
	}
	else if (t == 2)
	{
		hasLife = updateParticles3();
	} 
	else if (t == 3)
	{
	//	//hasLife = updateParticles4(ter);
	}
	else if (t == 4)
	{
		hasLife = updateParticles5();
	}
	return hasLife;
}

void particlehandler::display(float s)
{
	drawParticles(s);
}

bool particlehandler::initParticles()
{
	int iter;
	float maxL, minL, lif;
	// set max and min life values
	maxL = 1.0;
	minL = 0.5;
	// generate a random life between min and max
	//lif = minL + (float)(rand() % 100) / 100;
	lif = (float)(rand() % 50 / 100) + minL;
	// used to give max life a higher percentage
	if (lif >= maxL)
	{
		lif = maxL;
	}

	for (iter = 0; iter < max; iter++)
	{
		particle * p = new particle(true, lif, 0.01f);
		particles[iter] = *p;
	}
	return true;
}

bool particlehandler::generateParticles(int type)
{
	int xGrid, zGrid, yGrid, iter;

	// randomly generate a point
	xGrid = rand() % w.getWidth();
	zGrid = rand() % w.getLength();
	// get the height at the point
	yGrid = (int)w.getGrid()[xGrid * w.getWidth() + zGrid].getY();

	// set the initial position of each particle
	for (iter = 0; iter < max; iter++)
	{
		particles[iter].setPosition(vector3((float)xGrid, (float)yGrid, (float)zGrid));
		//particles[iter].setPosition(vector3(0.0f, 0.0f, 0.0f));

		// generate a random velocity for each particle
		float randx, randy, randz;
		
		if (type == 0)
		{
			randx = ((float)(rand() % 1001) / 1000 - 0.5f) * ((float)(rand() % 100) / 100);
			randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
			randz = ((float)(rand() % 1001) / 1000 - 0.5f) * ((float)(rand() % 100) / 100);

			// set gravity
			particles[iter].setGravity(vector3(0.0f, -0.02f, 0.0f));

			// set the color
			particles[iter].setColor(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (type == 1)
		{
			randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
			randy = ((float)(rand() % 1001) / 12500) * ((float)(rand() % 100) / 100);
			randz = ((float)(rand() % 1001) / 10000 - 0.50f) * ((float)(rand() % 100) / 100);

			// set gravity
			particles[iter].setGravity(vector3(0.0f, 0.0f, 0.0f));

			// set the color
			particles[iter].setColor(1.0f, 0.25f, 0.5f, 1.0f);
		}
		else if(type == 2)
		{
			// set global flag
			globalLife = false;
			globalIter = 0;
			xGrid = 0;
			yGrid = 0;
			zGrid = 0;

			// set position to 0,0
			particles[iter].setPosition(vector3(0.0, 0.0, 0.0));

			// set the random velocity
			randx = ((float)(rand() % 1001) / 10000) * ((float)(rand() % 100) / 100);
			randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
			randz = ((float)(rand() % 1001) / 10000) * ((float)(rand() % 100) / 100);

			randx += 0.3f;
			randy += 0.5f;
			randz += 0.3f;

			// set gravity
			particles[iter].setGravity(vector3(0.0f, -0.02f, 0.0f));

			// set the color
			particles[iter].setColor(0.0f, 0.8f, 1.0f, 1.0f);
		}
		//else if (type == 3)
		//{
		//	randx = ((float)(rand() % 1001) / 1000 - 0.5f) * ((float)(rand() % 100) / 100);
		//	randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
		//	randz = ((float)(rand() % 1001) / 1000 - 0.5f) * ((float)(rand() % 100) / 100);

		//	// set gravity
		//	particles[iter].setGravity(vector3(0.0f, -0.02f, 0.0f));

		//	// set the color
		//	particles[iter].setColor(0.2f, 0.0f, 1.0f, 1.0f);
		//	s = sph(*this);
		//}
		else if (type == 4 || type == 3)
		{
			xGrid = rand() % w.getWidth();
			zGrid = rand() % w.getLength();

			// set a random position in the sky
			particles[iter].setPosition(vector3(xGrid, 50, zGrid));

			randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
			randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
			randz = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);

			//particles[iter].setVelocity(vector3(randx, randy * -1, randz + 0.2f));
			randy += 0.2f;
			randy *= -1;
			randz += 0.1f;

			particles[iter].setColor(0.2, 0.2, 0.9, 0.75);

			particles[iter].setGravity(vector3(0, -0.2, 0));

			globalIter = 0;
			globalLife = false;
			if(type == 3) s = sph(this);
		}

		// set the initial velocity
		particles[iter].setVelocity(vector3(randx, randy, randz));
	}

	return true;
}

bool particlehandler::updateParticles()
{
	int iter;
	bool hasLife;
	hasLife = false;

	// iterate through the particles
	for (iter = 0; iter < max; iter++)
	{
		// if a particle has life, update it
		if (particles[iter].getIsAlive())
		{
			float yHeight = w.getGrid()[(int)particles[iter].getPosition().getX() * w.getWidth() + (int)particles[iter].getPosition().getZ()].getY();
			// check if we are below the terrain
			if (particles[iter].getPosition().getY() < yHeight - 1)
			{
				particles[iter].setIsAlive(false);
			}
			else 
			{
				//change the alpha
				particles[iter].setColor(particles[iter].getColor().getW() - 0.01,
										 particles[iter].getColor().getX(),
										 particles[iter].getColor().getY(),
										 particles[iter].getColor().getZ() - 0.01f);
				// update the velocity
				particles[iter].setVelocity(particles[iter].getVelocity() + particles[iter].getGravity());

				if (particles[iter].getPosition().getX() < 0 || 
				particles[iter].getPosition().getX() > (float)w.getWidth())
				{
					particles[iter].setVelocity(vector3(particles[iter].getVelocity().getX() * -1,
														particles[iter].getVelocity().getY(),
														particles[iter].getVelocity().getZ()));
				}
				if (particles[iter].getPosition().getZ() < 0 || 
					particles[iter].getPosition().getZ() > (float)w.getWidth())
				{
					particles[iter].setVelocity(vector3(particles[iter].getVelocity().getX(),
														particles[iter].getVelocity().getY(),
														particles[iter].getVelocity().getZ() * -1));
				}

				// update the position
				particles[iter].setPosition(particles[iter].getPosition() + particles[iter].getVelocity());
			
				hasLife = true;
			}
		}
	}
	return hasLife;
}

bool particlehandler::updateParticles2()
{
	int iter;
	float randL;
	
	// loop through the particles
	for (iter = 0; iter < max; iter++)
	{
		// check if the particle is alive
		if (particles[iter].getIsAlive())
		{
			// update and check the life of the particle
			if (particles[iter].getLife() < 0)
			{
				particles[iter].setIsAlive(false);
				continue;
			}

			randL = (float)(rand() % 100 / 90);

			// change the life
			particles[iter].setLife(particles[iter].getLife() - randL);

			// set the color and alpha
			particles[iter].setColor(particles[iter].getColor().getW(),
									 particles[iter].getColor().getX(),
									 particles[iter].getColor().getY(),
									 particles[iter].getColor().getZ() - 0.01f);

			float randx, randy, randz;
			// generate random values for the gravity
			randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
			randy = ((float)(rand() % 1001) / 12500) * ((float)(rand() % 100) / 100);
			randz = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);

			// update the gravity
			particles[iter].setGravity(vector3(randx, randy, randz));

			// update the velocity
			particles[iter].setVelocity(particles[iter].getVelocity() + particles[iter].getGravity());

			/*if (particles[iter].getPosition().getX() < 1 || 
				particles[iter].getPosition().getX() > (float)w.getWidth() - 1)
			{
				particles[iter].setVelocity(vector3(particles[iter].getVelocity().getX() * -1,
													particles[iter].getVelocity().getY(),
													particles[iter].getVelocity().getZ()));
			}
			if (particles[iter].getPosition().getZ() < 1 || 
				particles[iter].getPosition().getZ() > (float)w.getWidth() - 1)
			{
				particles[iter].setVelocity(vector3(particles[iter].getVelocity().getX(),
													particles[iter].getVelocity().getY(),
													particles[iter].getVelocity().getZ() * -1));
			}*/

			// update the position
			particles[iter].setPosition(particles[iter].getPosition() + particles[iter].getVelocity());
			
		}
	}
	return true;
}

bool particlehandler::updateParticles3()
{
	int iter, max;
	float randx, randy, randz;

	max = 100;
	// update the global var
	globalIter++;
	// check the position of the global
	if (globalIter >= max)
	{
		globalLife = true;
		globalIter = 0;
	}

	if (globalLife)
	{
		// set the random velocity
		randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
		randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
		randz = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);

		randy += 0.4f;

		if (globalIter % 5 == 0)
		{

			// update the position
			int direction, gridWidth, gridLength;

			// chose a random direction
			direction = rand() % 4;
			gridWidth = w.getWidth();
			gridLength = w.getLength();

			// direction leads to a cardinal direction
			// direction 0 - increment x
			if (direction == 0)
			{
				xGrid += 1;
				// if we are over the grid, reset
				if (xGrid >= gridWidth)
				{
					xGrid = gridWidth;
				}
				randx -= 0.5f;
			}
			// direction 1 - decrement x
			if (direction == 1)
			{
				xGrid -= 1;
				// if we are under the grid, reset
				if (xGrid < 0)
				{
					xGrid = 0;
				}
				randx += 0.5f;
			}
			// direction 2 - increment z
			if (direction == 2)
			{
				zGrid += 1;
				// if we are over the grid, reset
				if (zGrid >= gridLength)
				{
					zGrid = gridLength;
				}
				randz -= 0.5f;
			}
			// direction 3 - decrement z
			if (direction == 3)
			{
				zGrid -= 1;
				// if we are under the grid, reset
				if(zGrid < 0)
				{
					zGrid = 0;
				}
				randz += 0.5f;
			}
			
			// get the y
			yGrid = w.getGrid()[(int)xGrid * gridWidth + (int)zGrid].getY();
		}
	}

	if (globalLife)
	{
		for (iter = 0; iter < max; iter++)
		{
			// update the velocity
			particles[iter].setVelocity(particles[iter].getVelocity() + particles[iter].getGravity());
		
			// update the position
			particles[iter].setPosition(particles[iter].getPosition() + particles[iter].getVelocity());

			float yHeight;
			//yHeight = w.getGrid()[(int)particles[iter].getPosition().getX() * w.getWidth() + (int)particles[iter].getPosition().getZ()].getY();
			yHeight = 0;
			if (particles[iter].getPosition().getY() <= yHeight - 1)
			{
				particles[iter].setColor(0.0, 0.0, 0.0, 1.0);
			}
			else if (particles[iter].getPosition().getY() >= yHeight + 10)
			{
				particles[iter].setColor(1.0, 0.8, 0.0, 1.0);
			}
			else if (particles[iter].getPosition().getY() >= yHeight + 20)
			{
				particles[iter].setColor(0.8, 0.5, 0.5, 1.0);
			}
			else if (particles[iter].getPosition().getY() >= yHeight + 30)
			{
				particles[iter].setColor(0.0, 1.0, 1.0, 1.0);
			}
		}

		// reset the last particle
		//particles[globalIter].setPosition(vector3(xGrid, yGrid, zGrid));
		particles[globalIter].setPosition(vector3(0.0, 0.0, 0.0));

		particles[globalIter].setVelocity(vector3(randx, randy, randz));
	}
	else
	{
		// update only the living particles
		for (iter = 0; iter < globalIter; iter++)
		{
			// update the velocity
			particles[iter].setVelocity(particles[iter].getVelocity() + particles[iter].getGravity());
		
			// update the position
			particles[iter].setPosition(particles[iter].getPosition() + particles[iter].getVelocity());
		}
	}

	return true;
}

bool particlehandler::updateParticles4(terrain* t)
{
	s.run(&t);
	return true;
}

bool particlehandler::updateParticles5()
{
	int iter;
	float xgrid, zgrid, randx, randy, randz;

	globalIter += 5;
	if (globalIter >= max)
	{
		globalLife = true;
		globalIter = 0;
	}

	if (globalLife)
	{
		xgrid = rand() % w.getWidth();
		zgrid = rand() % w.getLength();

		// set a new random position
		particles[globalIter].setPosition(vector3(xgrid, 50, zgrid));

		randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
		randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
		randz = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);

		// set a new random velocity
		particles[globalIter].setVelocity(vector3(randx, (randy += 0.2f) * -1, randz + 0.1f));

		// update all particles
		for (iter = 0; iter < max; iter++)
		{
			//particles[iter].setVelocity(particles[iter].getVelocity() + particles[iter].getGravity());
			particles[iter].setPosition(particles[iter].getPosition() + particles[iter].getVelocity());

			if (particles[iter].getPosition().getY() <= 0)
			{
				//particles[iter].setColor(0.0, 0.0, 0.0, 0.0);

				xgrid = rand() % w.getWidth();
				zgrid = rand() % w.getLength();

				// set a new random position
				particles[iter].setPosition(vector3(xgrid, 50, zgrid));

				randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
				randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
				randz = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);

				// set a new random velocity
				particles[iter].setVelocity(vector3(randx, (randy += 0.2f) * -1, randz + 0.1f));
			}
		}
	}
	else
	{
		for (iter = 0; iter < globalIter; iter++)
		{
			//particles[iter].setVelocity(particles[iter].getVelocity() + particles[iter].getGravity());
			particles[iter].setPosition(particles[iter].getPosition() + particles[iter].getVelocity());
		
			if (particles[iter].getPosition().getY() <= 0)
			{
				//particles[iter].setColor(0.0, 0.0, 0.0, 0.0);

				xgrid = rand() % w.getWidth();
				zgrid = rand() % w.getLength();

				// set a new random position
				particles[iter].setPosition(vector3(xgrid, 50, zgrid));

				randx = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);
				randy = ((float)(rand() % 1001) / 750) * ((float)(rand() % 100) / 100);
				randz = ((float)(rand() % 1001) / 10000 - 0.05f) * ((float)(rand() % 100) / 100);

				// set a new random velocity
				particles[iter].setVelocity(vector3(randx, (randy += 0.2f) * -1, randz + 0.1f));
			}
		}
	}
	return true;
}

void particlehandler::drawParticles(float size, bool sphere)
{
	int iter;

	for (iter = 0; iter < max; iter++)
	{
		if (particles[iter].getIsAlive())
		{
			glColor4f(particles[iter].getColor().getW(), 
					  particles[iter].getColor().getX(), 
					  particles[iter].getColor().getY(), 
					  particles[iter].getColor().getZ());
			if(sphere){
				glPushMatrix();
				glutWireSphere(size/10, 16, 16);
				glTranslatef(particles[iter].getPosition().getX(),
					particles[iter].getPosition().getY(),
					particles[iter].getPosition().getZ());
				glPopMatrix();
			} else {
				glPointSize(size);
				glBegin(GL_POINTS);
					glVertex3f(particles[iter].getPosition().getX(), 
							   particles[iter].getPosition().getY(), 
							   particles[iter].getPosition().getZ());
				glEnd();
			}
		}
	}
}
particle* particlehandler::getParticles()	{	return particles;		}
spring* particlehandler::getSprings()		{	return springs;			}
int particlehandler::getMax()				{	return max;				}
int particlehandler::getSpringCount()		{	return springCount;		}

bool particlehandler::springExist(particle i, particle j){
	for(int k = 0; k < springCount; k++){
		if(springs[k].getStart() == i && springs[k].getEnd() == j)
			return true;
	}
	return false;
}
spring particlehandler::getSpring(particle i, particle j){
	for(int k = 0; k < springCount; k++){
		if(springs[k].getStart() == i && springs[k].getEnd() == j){
			return springs[k];
		}
	}
	return spring();
}
void particlehandler::addSpring(spring i){
	springCount ++;
	spring* s = springs;
	springs = new spring[springCount];
	springs = s;
	springs[springCount - 1] = i;
}
void particlehandler::removeSpring(spring i){
	springCount --;
	spring* s = springs;
	springs = new spring[springCount];
	for(int i = 0; i < springCount; i++){
		springs[i] = s[i];
	}
}