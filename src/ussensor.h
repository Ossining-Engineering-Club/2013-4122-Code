/***************************************************************************************
 *
 * Declare the Interface for the Ossining High School Robot
 * 
 */
#ifndef USSENSOR_H_		//Checks if subsys.h has already been included
#define USSENSOR_H_		//Set USSENSOR_H when ussensor.h is included to prevent it from being included multiple times
#include "WPILib.h"		//Include the FRC Library


/*
 * Ultrasonic Sensor Class
 */
class USSensor
{
	public:
		USSensor(UINT32 channel);	//Constructor to intialize - default is off
		void getsample(void);	//This is used for taking a sample
		float getrange(void);	//Find the range using the sensor
		void setscale(float);	//Set the scale that will be used by the sensor
	private:
		AnalogChannel uschannel;
		float averagerange;		//Variable accumulates average range
		float feetpervolt;
};
#endif
