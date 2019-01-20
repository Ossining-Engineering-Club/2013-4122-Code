#ifndef LASERFRISBEE_H_
#define LASERFRISBEE_H_
#include "WPILib.h"
#define distpoints 7
class rangefrisbee
{
public:
	rangefrisbee();
	float getDistance(float);
	float getAngle(float);
	float getSpeed();//gets speed for last angle or distance sent to function
private:
	float distable[distpoints][3];//0 is dist and 1 is angle
	float distance,angle,speed;//dist should be in feet, a
	//angle should be -1 to 1 so it can be passed directly to the jaguar
	//passing angle will bypass manual angle control entirely
};
#endif
