#include "HookSensor.h"
#include "WPILib.h"
HookSensor::HookSensor(UINT32 ch1, UINT32 ch2):
	analog1(ch1),
	analog2(ch2)
{
	//do nothing
}
bool HookSensor::returnState1()
{
	if(analog1.GetVoltage()>=1)
	{
		state1=true;
	}
	else
	{
		state1=false;
	}
	return state1;
}
bool HookSensor::returnState2()
{
	if(analog2.GetVoltage()>=1)
	{
		state2=true;
	}
	else
	{
		state2=false;
	}
	return state2;
}
char* HookSensor::getStatus()
{
	if(analog2.GetVoltage()>=1)
		{
			state2=true;
		}
	else
		{
			state2=false;
		}
	if(analog1.GetVoltage()>=1)
		{
			state1=true;
		}
	else
		{
			state1=false;
		}
	
	if(!state1 && !state2) return "off bar";
	else if(state1 && !state2) return "LEFT ON";
	else if(!state1 && state2) return "RGHT ON";
	else if(state1 && state2) return "*LOCKED*";
	else return "No Status";
}
