#include "water.h"

water::water(void)
{
	waves = true;
	iterator = 0;
}

water::~water(void)
{
}

void water::display(float size){
	glPointSize(size);
	glBegin(GL_POINTS);
	for(int i = 0; i < pMax; i++){
		if(particles[i].getIsAlive()){
			glVertex3f(particles[i].getPosition().getX(),
				particles[i].getPosition().getY(),
				particles[i].getPosition().getZ());
		}
	}
	glEnd();
}
void water::update(world w){
	// have water drop, until it hits terrain
	// for each particle, drop until it is at the terrain
	vector3 current;
	vector3 current2;
	for(int i = 0; i < pMax; i ++){
		current = particles[i].getPosition();
		if(current.getY() > w.getPoint(current.getX(), current.getY()).getY()){	
			/*for(int j = 0; j < pMax; j++){
				current2 = particles[j].getPosition();
				if(current2.getX() == current.getX() && current2.getZ() == current.getZ() &&
					current2.getY() < current.getY())
				{*/
					particles[i].setPosition(vector3(current.getX(),
						current.getY() - 1, current.getZ()));	
				/*}	
			}	*/				
		} 
	}
}
void water::generate(int waterHeight, int waterFloor, int xBound, int yBound){
	alive = true;
	// set up particles
	pMax = waterHeight*xBound*yBound;
	particles = new particle[pMax];

	// loop through the map n-particles times placing partices
	// on the proper x,z spots on the proper y-waterHeight
	int i = 0;
	particle *p;
	for(int y = waterFloor; y < waterHeight; y++){
		for(int x = 0; x < xBound; x++){
			for(int z = 0; z < yBound; z++){
				p = new particle(true, -1, -1);
				p->setPosition(vector3((float)x,(float)y,(float)z));
				particles[i] = *p;
				
				// increment i
				i++;
			}
		}
	}
}

void water::toggleWaves(){
	waves = !waves;
}
bool water::isAlive(){ return alive; }
int water::getPMax(){ return pMax; }
particle* water::getParticles(){ return particles; }