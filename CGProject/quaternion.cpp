#include "quaternion.h"

quaternion::quaternion(void)
{
	w = 1;
	x = y = z = 0;
}

quaternion::quaternion(float d, float a, float b, float c){
	w = d;
	x = a;
	y = b;
	z = c;
}
quaternion::~quaternion(void)
{
}

double quaternion::length(){
	return sqrt(w*w + x*x + y*y + z*z);
}

// TODO: Check if this works
quaternion quaternion::normalize(){
	float l = (float)length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
	return *this;
}

quaternion quaternion::conjugate(){
	quaternion q(w, -x,-y,-z);
	return q;
}

quaternion quaternion::operator *(const quaternion &rhs){
	quaternion q;
	quaternion lhs = *this;
	q.x = lhs.w*rhs.x + lhs.x*rhs.w + lhs.y*rhs.z - lhs.z*rhs.y;
	q.y = lhs.w*rhs.y - lhs.x*rhs.z + lhs.y*rhs.w + lhs.z*rhs.x;
	q.z = lhs.w*rhs.z + lhs.x*rhs.y - lhs.y*rhs.x + lhs.z*rhs.w;
	q.w = lhs.w*rhs.w - lhs.x*rhs.x - lhs.y*rhs.y - lhs.z*rhs.z;
	return q; 
}

float* quaternion::toMatrix(bool normalized){
	if(normalized){
		float m[16] = { 1 - 2*y*y - 2*z*z, 2*x*y - 2*w*z, 2*x*z + 2*w*y, 0,
						2*x*y + 2*w*z, 1 - 2*x*x - 2*z*z, 2*y*z - 2*w*x, 0,
						2*x*z - 2*w*y, 2*y*z - 2*w*x, 1-2*x*x - 2*y*y, 0,
						0, 0, 0, 1};
		return m;
	} else {
		float m[16] = { w*w + x*x + y*y + z*z, 2*x*y - 2*w*z, 2*x*z + 2*w*y, 0,
						2*x*y + 2*w*z, w*w - x*x + y*y - z*z, 2*y*z - 2*w*x, 0,
						2*x*z - 2*w*y, 2*y*z - 2*w*x, w*w - x*x - y*y + z*z, 0,
						0,0,0,1};
		return m;
	}
}