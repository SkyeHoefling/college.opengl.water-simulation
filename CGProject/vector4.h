#pragma once

class vector4
{
public:
	vector4(void);
	vector4(float wp, float xp, float yp, float zp);
	~vector4(void);
	float getW();float getX();float getY();float getZ();
	void setW(float i);void setX(float i);void setY(float i);void setZ(float i);
	float dot(vector4 i);
	vector4 operator+(vector4 rhs);
	vector4 operator-(vector4 rhs);
	bool operator==(vector4 rhs);
protected:
	float w, x, y, z;
};
