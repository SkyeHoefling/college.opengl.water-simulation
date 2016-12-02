#include "spring.h"

spring::spring(void)
{
}

spring::spring(particle s, particle e){
	start = s;
	end = e;
	distance =s.getPosition().distanceFrom(e.getPosition());
	restLength = distance;
}
spring::~spring(void)
{
}

particle spring::getStart()				{		return start;			}
particle spring::getEnd()				{		return end;				}
float spring::getDistance()				{		return distance;		}
float spring::getRestLength()			{		return restLength;		}
void spring::setRestLength(float i)		{		restLength = i;			}