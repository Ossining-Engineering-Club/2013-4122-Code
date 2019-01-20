#ifndef CLIMBER_H_ //Creates definition of climber library
#define CLIMBER_H_ //Creates def of climber as well
#include "WPILib.h" //allows us to use all the stuff in this library
class Climber
{
	public:
		Climber(UINT32, UINT32);	//Define channel numbers for Arm and Cable
		void climbAllow(bool);		//if a button is pressed, the climber will be turned off (killswitch)
		void cableAdjust(float);	//takes the value of a floating point number (ie:Joystick.GetX()), sets motor speed to it.
		void armAdjust(float);		//see above
	private:
		bool mode;//allows or disallows the cable to move, we adjust this in climb allow 
		bool modeAssist;// Becomes true when button is pushed
		//if a button is pressed, the climber will be turned on, if we press another, the climber is off (so the tank drive can be on)
		//we might not actually need this
		Jaguar Arm;
		Jaguar Cable;	//Use PWM to 2 Jaguars driving 2 motors pulling the cable
};
#endif//obots-code@googlegroups.com
