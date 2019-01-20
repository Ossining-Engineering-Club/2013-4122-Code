/*this is the code that controls the robots drive
 * 
 * 
 */
#ifndef tankdrivethrottle_H_	//this defines thank drive throttle for later use
#define tankdrivethrottle_H_	//this defines it as a variable
#include "WPILib.h"	//includes WPILib library

class TankDriveThrottle	//stating for later use
{
	public:	//enables incorporation of additional code
		TankDriveThrottle(UINT32,UINT32);
		void drive(float,float); //makes the robot drive 
		//takes two floating points ie: joystick axes
		void throttle(float);//CONTROLS JOYSTICK SENSITIVITY/topspeed
	private:	//secludes a name for usage only in this code
		Jaguar left;
		Jaguar right;
		float conthrottle;
};
#endif 	//finir
