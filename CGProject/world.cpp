#include "world.h"

world::world(void)
{
	width = 64;
	length = 64;
	gSize = width * length;
	grid = new vector3[gSize];//dWidth * dLength];
	initializeGrid();
}

world::world(int w, int l){
	width = w;
	length = l;
	gSize = width * length;
	grid = new vector3[gSize];
	initializeGrid();
}
world::~world(void)
{
}

void world::initializeGrid(){
	int counter = 0;
	for(int i = 1; i < width+1; i++){
		for(int j = 1; j < length+1; j++){
			grid[counter].setX((float)i);
			grid[counter].setY(1.0f);
			grid[counter].setZ((float)j);
			counter++;
		}
	}
}

int world::getWidth(){ return width; }
int world::getLength(){ return length; }
vector3* world::getGrid(){ return grid; }
vector3 world::getPoint(float x, float z){
	for(int i = 0; i < gSize; i ++){
		if(grid[i].getX() == x && grid[i].getZ() == z){
			return vector3(x,grid[i].getY(), z);
		}
	}
	return vector3();
}
vector3 world::getSurfaceNormal(vector3 p1, vector3 p2, vector3 p3){
	vector3 u = p2 - p1;
	vector3 v = p3 - p1;
	vector3 n;
	n.setX( (u.getY()*v.getZ()) - (u.getZ()*v.getY()) );
	n.setY( (u.getZ()*v.getX()) - (u.getX()*v.getZ()) );
	n.setZ( (u.getX()*v.getY()) - (u.getY()*v.getX()) );
	return n;
}
void world::getAllNormals(){
	gridNormals = new vector3[gSize];
	for(int i = 0; i < getLength(); i ++){
		//for(int j = 0; j < getWidth(); j ++){
			//gridNormals[j + ( i * getWidth()] = getSurfaceNormal[j +
		//}
	}
	/*for(int i = 0; i < gSize; i ++){
		gridNormals[i] = getSurfaceNormal(grid[i].getVector(),
			grid[i+1], grid[i+2]);
		gridNormals[i] = grid[i].getVector().normalize();
	}*/
}
void world::toggleShowNormals(){showNormals = !showNormals;}
void world::drawNormals(){
	if(showNormals){
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);
			for(int i = 0; i < gSize; i ++){
					glVertex3f(grid[i].getX(), grid[i].getY(), grid[i].getZ());
					glVertex3f(grid[i].getX() + gridNormals[i].getX(),
							   grid[i].getY() + gridNormals[i].getY(),
							   grid[i].getZ() + gridNormals[i].getZ());
			}
		glEnd();
	}
}
void world::setPointAt(int i, float x, float y, float z){
	grid[i].setX(x); grid[i].setY(y); grid[i].setZ(z);
}
void world::setPointAtX(int i, float x){
	grid[i].setX(x);
}
void world::setPointAtY(int i, float y){
	grid[i].setY(y);
}
void world::setPointAtZ(int i, float z){
	grid[i].setZ(z);
}