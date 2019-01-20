//for the robot: initialize with left as the first argument, right as the second
//you need to run the process() method every time you want to update
//the print string to be sent to lcd can be described in main as <hooksensor instance name>.returnline 
//just send that to the LCD in the normal fashion.
#ifndef HOOKSENSOR_H_
#define HOOKSENSOR_H_
#include "WPILib.h"

class HookSensor

{

public:
	HookSensor(UINT32, UINT32);
	bool returnState1();
	bool returnState2();
	char* getStatus();
	
private:
	AnalogChannel analog1;
	AnalogChannel analog2;
	bool state1;
	bool state2;
};
#endif
