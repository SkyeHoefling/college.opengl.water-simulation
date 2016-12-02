#include "triangle.h"

triangle::triangle(void)
{
	p1 = p2 = p3 = vector3();
	calculateCenter();
	calculateNormal();
}

triangle::triangle(vector3 a, vector3 b, vector3 c){
	p1 = a;
	p2 = b;
	p3 = c;	
	calculateCenter();
	calculateNormal();
}

triangle::~triangle(void)
{
}

vector3 triangle::getP1(){ return p1; }
vector3 triangle::getP2(){ return p2; }
vector3 triangle::getP3(){ return p3; }
vector3 triangle::getNormal()	{	return normal;	}
vector3 triangle::calculateNormal(){
	vector3 v = p2 - p1;
	vector3 u = p3 - p1;
	normal = u.cross(v).normalize();
	return normal;
}
vector3 triangle::calculateCenter(){
	center = (p1 + p2 + p3) / 3;
	return center;
}
void triangle::drawNormal(){
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex3f(center.getX(), center.getY(), center.getZ());
	glVertex3f(center.getX() + normal.getX(), 
		center.getY() + normal.getY(), center.getZ() + normal.getZ());
	glEnd();
		
}
triangle triangle::triangleAt(vector3 i){
	return triangle();
}
bool triangle::sameSide(vector3 p1, vector3 p2, vector3 a, vector3 b){
	vector3 cp1 = (b - a).cross(p1 - a);
	vector3 cp2 = (b - a).cross(p2 - a);
	if(cp1.dot(cp2) >= 0) return true;
	else return false;
}
bool triangle::pointInTri(vector3 i){
	if(sameSide(i, p1, p2, p3) && sameSide(i, p2, p1, p3) &&
		sameSide(i, p3,p1,p2)) return true;
	else return false;
}