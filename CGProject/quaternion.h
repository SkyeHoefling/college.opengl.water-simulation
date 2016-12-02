#pragma once
#include "vector4.h"
#include <math.h>

class quaternion: public vector4
{
public:
	quaternion(void);
	quaternion(float d, float a, float b, float c);
	~quaternion(void);
	double length();
	quaternion normalize();
	quaternion conjugate();
	quaternion operator*(const quaternion &rhs);
	float* toMatrix(bool normalized);
};
