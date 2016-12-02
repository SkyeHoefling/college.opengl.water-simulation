#include "vector2.h"

vector2::vector2(void)
{
	x = y = 0;
}

vector2::vector2(float a, float b){
	x = a;
	y = b;
}

vector2::~vector2(void)
{
}

void vector2::setX(float i)		{	x = i;		}
void vector2::setY(float i)		{	y = i;		}

void vector2::addX(float i)		{	x += i;		}
void vector2::addY(float i)		{	y += i;		}

float vector2::getX()			{	return x;	}
float vector2::getY()			{	return y;	}

float vector2::dot(vector2 i){	
	return x*i.getX() + y*i.getY();	
}