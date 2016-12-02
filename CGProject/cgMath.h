#pragma once
#include <math.h>
#include "vector3.h"

class cgMath
{
public:
	cgMath(void);
	~cgMath(void);
	vector3 absolute(vector3 i);
	vector3 project(vector3 u, vector3 v);
};
