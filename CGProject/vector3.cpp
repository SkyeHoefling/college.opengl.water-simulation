#include "vector3.h"

vector3::vector3(void)
{
	x = y = z = 0.0f;
}

vector3::~vector3(void)
{
}

vector3::vector3(float xp, float yp, float zp){
	x = xp;
	y = yp;
	z = zp;
}

void vector3::setX(float i){ x = i; }
void vector3::setY(float i){ y = i; }
void vector3::setZ(float i){ z = i; }
void vector3::addX(float i){ x += i; }
void vector3::addY(float i){ y += i; }
void vector3::addZ(float i){ z += i; }
float vector3::getX(){ return x; }
float vector3::getY(){ return y; }
float vector3::getZ(){ return z; }
vector3 vector3::getVector(){ return *this; }
vector3 vector3::operator +(vector3 rhs){
	return vector3(x+rhs.getX(), y+rhs.getY(), z+rhs.getZ());
}
vector3 vector3::operator -(vector3 rhs){
	return vector3(x-rhs.getX(), y-rhs.getY(), z-rhs.getZ());
}
vector3 vector3::operator *(float rhs){
	return vector3(x*rhs, y*rhs, z*rhs);
}
vector3 vector3::operator *(int rhs){
	return vector3(x*rhs, y*rhs, z*rhs);
}
vector3 vector3::operator *(vector3 rhs){
	return vector3(x*rhs.getX(), y*rhs.getY(), z*rhs.getZ());
}
vector3 vector3::operator /(float rhs){
	return vector3(x/rhs, y/rhs, z/rhs);
}
vector3 vector3::operator /(int rhs){
	return vector3(x/rhs, y/rhs, z/rhs);
}
bool vector3::operator ==(vector3 rhs){
	if(x==rhs.getX() && y==rhs.getY() && z==rhs.getZ())
		return true;
	return false;
}
vector3 vector3::normalize(){
	float l = length();
	return vector3(x/l, y/l, z/l);
}

vector3 vector3::unitFrom(vector3 v){
	vector3 vec(x-v.getX(), y-v.getY(), z-v.getZ());
	return vec.normalize();
}
float vector3::dot(vector3 i){ return x*i.getX() + y*i.getY() + z*i.getZ(); }

vector3 vector3::cross(vector3 i)
{
	vector3 normal;
	normal.setX(y * i.getZ() - z * i.getY());
	normal.setY(z * i.getX() - x * i.getZ());
	normal.setZ(x * i.getY() - y * i.getX());

	return normal;
}

float vector3::length(){
	return sqrt(x*x + y*y + z*z);
}
float vector3::distanceFrom(vector3 v){
	return sqrt(x*v.getX() + y*v.getY() + z*v.getZ());
}