#pragma once

class vector2
{
private:
	float x;
	float y;
public:
	vector2(void);
	vector2(float a, float b);
	~vector2(void);
	
	// Setters
	void setX(float i);
	void setY(float i);

	// incrementors
	void addX(float i);
	void addY(float i);

	// getters
	float getX();
	float getY();

	float dot(vector2 i);
};
