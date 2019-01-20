#ifndef SHOOTER_H_	
#define SHOOTER_H_	//Set SHOOTER_h when example is included to prevent it from being included multiple times
#include "WPILib.h"	//Include the FRC Library
class Shooter
{
	public:
		Shooter(UINT32, UINT32, UINT32, UINT32, UINT32);
		void spinnerson(void);			//Turns the spinners on
		void spinnersoff(void);			//Turns the spinners off
		void settarget(void);			//Sets target range
		void spinspeed(float,float);	//Sets spin speed and ratio
		void shoot(void);				//Moves the shoot arm
		void shootmultiple(int);		//Autonomous - Shoot n frisbees at given speed
		void returnarm(void); 			//return arm after shooting
		void shootarmstop(void);		//stop moving the shooter arm
		float setangle(float);			//Set the shooting angle
	private:
		Jaguar spinforward;
		Jaguar spinbackward;
		Jaguar shootarm;
		Jaguar shootangle;
		AnalogChannel pospot;//position potentiometer
		float speed;
		float ratio;
};
#endif
