#pragma once
#include <math.h>
class vector3
{
public:
	vector3(void);
	vector3(float x, float y, float z);
	~vector3(void);
	float getX(); 
	float getY();
	float getZ();
	void setX(float i);
	void setY(float i);
	void setZ(float i);
	void addX(float i);
	void addY(float i);
	void addZ(float i);
	vector3 operator+(vector3 rhs);
	vector3 operator-(vector3 rhs);
	vector3 operator*(float rhs);
	vector3 operator*(int rhs);
	vector3 operator*(vector3 rhs);
	vector3 operator/(float rhs);
	vector3 operator/(int rhs);
	bool operator==(vector3 rhs);
	vector3 getVector();
	vector3 normalize();
	vector3 unitFrom(vector3 v);
	float dot(vector3 i);
	vector3 cross(vector3 i);
	float length();
	float distanceFrom(vector3 v);
	
protected:
	float x, y, z;
};
