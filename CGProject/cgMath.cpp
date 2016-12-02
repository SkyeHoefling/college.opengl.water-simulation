#include "cgMath.h"

cgMath::cgMath(void)
{
}

cgMath::~cgMath(void)
{
}

vector3 cgMath::absolute(vector3 i){
	return vector3(abs(i.getX()),
	   			   abs(i.getY()),
				   abs(i.getZ()));
}
vector3 cgMath::project(vector3 u, vector3 v){
	float dot = u.dot(v);
	float b = sqrt(v.getX()*v.getX() + v.getY()*v.getY() + v.getZ()*v.getZ());
	float bottom = b*b;
	float left = dot / bottom;
	return vector3( left*v.getX(), left*v.getY(), left*v.getZ() );
}