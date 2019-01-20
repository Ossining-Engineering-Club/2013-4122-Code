/***************************************************************************************
 *
 * Declare the Interface for the Ossining High School Robot
 * 
 */
#ifndef DELAY_H_		//Checks if subsys.h has already been included
#define DELAY_H_		//Set DELAY_H when ussensor.h is included to prevent it from being included multiple times
#include "WPILib.h"		//Include the FRC Library


/*
 * Ultrasonic Sensor Class
 */
class AutoDelay
{
	public:
		AutoDelay(UINT32 channel);	//Constructor to intialize - default is off
		float getsample(void);	//This is used for taking a sample
		
	private:
		AnalogChannel uschannel;
		float delaytime;
		
};
#endif
