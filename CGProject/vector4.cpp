#include "vector4.h"

vector4::vector4(void)
{
}

vector4::vector4(float wp, float xp, float yp, float zp){
	w = w;
	x = x;
	y = y;
	z = z;
}

vector4::~vector4(void)
{
}


float vector4::getW(){ return w; }
float vector4::getX(){ return x; }
float vector4::getY(){ return y; }
float vector4::getZ(){ return z; }
void vector4::setW(float i){ w = i; }
void vector4::setX(float i){ x = i; }
void vector4::setY(float i){ y = i; }
void vector4::setZ(float i){ z = i; }
vector4 vector4::operator +(vector4 rhs){
	return vector4(w+rhs.getW(),x+rhs.getX(), y+rhs.getY(), z+rhs.getZ());
}
vector4 vector4::operator -(vector4 rhs){
	return vector4(w-rhs.getW(), x-rhs.getX(), y-rhs.getY(), z-rhs.getZ());
}
bool vector4::operator ==(vector4 rhs){
	if(x==rhs.getW() && x==rhs.getX() && y==rhs.getY() && z==rhs.getZ())
		return true;
	return false;
}
