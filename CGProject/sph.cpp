#include "sph.h"

sph::sph(void)
{
}
sph::sph(particlehandler* p){
	pHandler = p;
	gravity = -0.02f;
	changeInTime = 1.0f;
	interactionRadius = 2.5f; // 5
	stiffness = 1.5f; //3.5
	stiffnessNear = 2.0f; //4
	restDensity = 0.5f;
	springConstant = 0.05f;
	plasticityConstant = 0.03f;
}
sph::sph(particlehandler* p, float g, float t, float r, float s, float sn, float d, float sk, float pk){
	pHandler = p;
	gravity = g;
	changeInTime = t;
	interactionRadius = r;
	stiffness = s;
	stiffnessNear = sn;
	restDensity = d;
	springConstant = sk;
	plasticityConstant = pk;
}
sph::~sph(void)
{
}

void sph::run(terrain** t){
	// for each particle apply gravity
	for(int i = 0; i < pHandler->getMax(); i++){
		// vi <-- vi + delta t*g
		pHandler->getParticles()[i].setVelocity(pHandler->getParticles()[i].getVelocity() +
			vector3(0, changeInTime * gravity, 0));
	}

	// modify velocities w/ pairwise viscosity impulses
	viscosityImpulses();
	
	// update each particle's position
	for(int i = 0; i < pHandler->getMax(); i++){
		// save previous position
		pHandler->getParticles()[i].setPrevPosition(pHandler->getParticles()[i].getPosition());
		// advance to predicted position
		pHandler->getParticles()[i].setPosition(pHandler->getParticles()[i].getPosition() + 
			(pHandler->getParticles()[i].getVelocity() * changeInTime) );
	}

	// add and remove springs, change rest lengths
	springAdjustment();

	// modify positions according to springs,
	// double density relaxation and collisions
	springDisplacements();
	doubleDensityRelaxation();

	for(int i = 0; i < pHandler->getMax(); i ++){
		// for each particle i use previous position to comput next velocity
		pHandler->getParticles()[i].setVelocity( (pHandler->getParticles()[i].getPosition() -
			pHandler->getParticles()[i].getPrevPosition() )/ changeInTime);
	}

	// resolve collisions
	particleBodyInteractions(&t);	
}

void sph::doubleDensityRelaxation(){
	float q;
	vector3 dx;
	vector3 d;
	cgMath helper;
	for(int i = 0; i < pHandler->getMax(); i ++){
		// set the densities to 0
		pHandler->getParticles()[i].setDensity(0);
		pHandler->getParticles()[i].setDensityNear(0);
		// compute density and near density based on neighbors
		for(int j = 0; j < pHandler->getParticles()[i].getNeighborsCount(); j ++){
			// q = |position[j] - position[i]|.length
			q = (helper.absolute(pHandler->getParticles()[i].getNeighbors()[j].getPosition() -
				pHandler->getParticles()[i].getPosition() ) 
				/ interactionRadius).length();
			
			// if q is less than 1
			if(q < 1){
				// set the density and the near density
				pHandler->getParticles()[i].getNeighbors()[j].setDensity(pHandler->getParticles()[i].getNeighbors()[j].getDensity()
					 + ( (1 - q) * (1 - q) ) );
				pHandler->getParticles()[i].getNeighbors()[j].setDensityNear(
					pHandler->getParticles()[i].getNeighbors()[j].getDensityNear() + 
					( (1 - q) * (1 - q) * (1 - q) ) );
			}		
		}
		// compute pressure and near pressure
		pHandler->getParticles()[i].setPressure(stiffness * 
			( pHandler->getParticles()[i].getDensity() - restDensity) );
		pHandler->getParticles()[i].setPressureNear(stiffnessNear *
			pHandler->getParticles()[i].getDensityNear());
		// set dx <- 0
		dx = vector3(0,0,0);
		for(int j = 0; j < pHandler->getParticles()[i].getNeighborsCount(); j++){
			// q = |position[j] - position[i]|.length
			q = (helper.absolute(pHandler->getParticles()[i].getNeighbors()[j].getPosition() -
				pHandler->getParticles()[i].getPosition() ) 
				/ interactionRadius).length(); 
			if(q < 1){
				// apply displacements
				d = ( ( (pHandler->getParticles()[i].getPosition() - 
					pHandler->getParticles()[i].getNeighbors()[j].getPosition()).normalize() ) *
					changeInTime * changeInTime * 
					(pHandler->getParticles()[i].getNeighbors()[j].getPressure() * 
					(1 - q) + pHandler->getParticles()[j].getPressureNear() *
					( (1 - q) * (1 - q) ) ) );
				pHandler->getParticles()[j].setPosition(pHandler->getParticles()[i].getNeighbors()[j].getPosition() +
					d / 2);
				dx = dx - d/2;
			}
		}
		pHandler->getParticles()[i].setPosition(pHandler->getParticles()[i].getPosition()
			+ dx);
	}
}
void sph::springDisplacements(){
	vector3 d;
	// attributes for the start and end spring
	//for readability 
	particle s;
	particle e;
	// for each spring ij(i - start; j - end)
	for(int i = 0; i < pHandler->getSpringCount(); i++){
		s = pHandler->getSprings()[i].getStart();
		e = pHandler->getSprings()[i].getEnd();
		// calculate some nasty math
		d = vector3(s.getPosition()).unitFrom(e.getPosition()) * 
			changeInTime*changeInTime * springConstant * 
			(1 - pHandler->getSprings()[i].getRestLength()/interactionRadius) *
			(pHandler->getSprings()[i].getRestLength() - 
				s.getPosition().distanceFrom(e.getPosition()) );
		
		// apply the start position and end position
		pHandler->getSprings()[i].getStart().setPosition(pHandler->getSprings()[i].getStart().getPosition() -
			d/2);
		pHandler->getSprings()[i].getEnd().setPosition(pHandler->getSprings()[i].getEnd().getPosition() +
			d/2);
	}
}
void sph::springAdjustment(){
	float q;
	float rij;
	particle* cNeighbors;
	particle* cParticles = pHandler->getParticles();
	spring cSpring;
	float d;		//tolerableDeformation
	float yieldRatio = 0.1f;// range from 0-0.2
	// for each neighbor pair ij, (i<j)
	for(int i = 0; i < pHandler->getMax(); i++){		
		cNeighbors = pHandler->getParticles()[i].getNeighbors();
		for(int j = 0; j < pHandler->getParticles()[i].getNeighborsCount(); j++){
			if(pHandler->getParticles()[i].getPosition().length() < pHandler->getParticles()[i].getNeighbors()[j].getPosition().length()){
				// q <- rij/h
				// rij = distance between i,j				
				rij = cNeighbors[j].getPosition().distanceFrom(cParticles[i].getPosition());
				q =  rij / interactionRadius;
				if(q < 1){
					// if there is no spring ij make one and use it
					if(!pHandler->springExist(cParticles[i], cNeighbors[j])){
						// create a new spring with i,j as start,end
						// add spring ij with rest length h
						pHandler->addSpring(spring(cParticles[i], cNeighbors[j]));
					} else {
						cSpring = pHandler->getSpring(cParticles[i], cNeighbors[j]);
					}
					// tolerable deformation = yield ratio * rest length
					d = yieldRatio * cSpring.getRestLength();

					// if rij > L + d
					// else if rij < L - d
					if(rij > cSpring.getRestLength() + d){
						// apply some stretching math
						cSpring.setRestLength(cSpring.getRestLength() + changeInTime *
							plasticityConstant * (rij - cSpring.getRestLength() - d));

					} else if(rij < cSpring.getRestLength() - d){
						// apply some compressing math
						cSpring.setRestLength(cSpring.getRestLength() - changeInTime *
							plasticityConstant * (cSpring.getRestLength() - d - rij));
					}
				}
			}
		}
	}

	// for each spring ij
	// if the current springs resting length > interation radius (h) remove that spring
	for(int i = 0; i < pHandler->getSpringCount(); i++){
		if(pHandler->getSprings()[i].getRestLength() > interactionRadius){
			pHandler->removeSpring(pHandler->getSprings()[i]);
		}
	}
}
void sph::viscosityImpulses(){
	cgMath m;
	particle* cNeighbors;
	particle* cParticles = pHandler->getParticles();
	float u;
	float rij;
	float q;
	vector3 impulse;
	// made up numbers
	float sigma = 0.1f;	// increase for less viscosity fluid	
	float beta = 0.6f;	// needs to be non-zero
	// for each neighbor pair ij, (i<j)
	for(int i = 0; i < pHandler->getMax(); i++){		
		cNeighbors = pHandler->getParticles()[i].getNeighbors();
		for(int j = 0; j < pHandler->getParticles()[i].getNeighborsCount(); j++){
			if(pHandler->getParticles()[i].getPosition().length() < pHandler->getParticles()[i].getNeighbors()[j].getPosition().length()){
				// q <- rij / h
				// rij <- distance between i,j	
				rij = cNeighbors[j].getPosition().distanceFrom(cParticles[i].getPosition());
				q =  rij / interactionRadius;
				if (q < 1){
					// inward radial velocity
					// u <- (vi-vj)* rij.normal()
					u = m.project( ( cParticles[i].getVelocity() - cNeighbors[j].getVelocity() ), 
						vector3(cParticles[i].getPosition()).unitFrom(
						cNeighbors[j].getPosition())).length();
					if (u > 0){
						// linear and quadratic impulses
						impulse = vector3(cParticles[i].getPosition()).unitFrom(
							cNeighbors[j].getPosition()) *
							changeInTime * ( 1 - q ) * (sigma * u + beta * u*u );
						pHandler->getParticles()[i].setVelocity(pHandler->getParticles()[i].getVelocity() -
							impulse/2);
						pHandler->getParticles()[i].getNeighbors()[j].setVelocity(
							pHandler->getParticles()[i].getNeighbors()[j].getVelocity() +
							impulse/2);
					}
				}
			}
		}
	}
}
vector3 sph::collisionImpulse(particle* p, float mew, terrain**** t){
	vector3 normal;
	normal = (***t)->getTri(&p->getPosition()).calculateNormal();
	// velocity Normal = ( velocity dot object normal)object normal
	vector3 velocityNormal = normal * (p->getVelocity().dot(normal));
	// Vt = V - Vn
	// V = Vi - Vp where Vp = object velocity which is 0
	vector3 velocityTangent = p->getVelocity();
	// impulse = Vnormal - mew * Vtangent
	vector3 impulse = velocityNormal - (velocityTangent * mew);
	return impulse;
}
void sph::particleBodyInteractions(terrain*** t){	
	/*foreach particle inside a body
		compute collision impulse I
		apply I to the particle
		extract the particle if still inside the body*/
	vector3 bodyVelocity(0.0f,0.0f,0.0f);		// vp (velocity at contact point is always 0,0,0)
	vector3 impulse;
	particle* cParticles = pHandler->getParticles();
	int m = pHandler->getMax();
	// friction constant
	float mew = 0.25f; // 0 == slippage, 1 == no slippage
	for(int i = 0; i < m; i ++){
		// check if we are intersecting
		(**t)->get
		impulse = collisionImpulse(&cParticles[i], mew, &t);
		// apply impulse to particle
		impulse.setY(-impulse.getY());
		pHandler->getParticles()[i].setVelocity(/*cParticles[i].getVelocity() +*/ 
			impulse);
	}
}