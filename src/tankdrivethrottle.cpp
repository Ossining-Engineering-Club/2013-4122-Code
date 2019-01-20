#include "tankdrivethrottle.h"	// includes tank drive in this code
#include "WPILib.h"	//includes WPILib bibrary 
TankDriveThrottle::TankDriveThrottle(UINT32 leftchannel, UINT32 rightchannel):
	left(leftchannel),
	right(rightchannel)
	{
	conthrottle=0;
	}
void TankDriveThrottle::drive(float leftstick,float rightstick)//since their is a void, their will be input but no output
//^^this line enables joysticks to have left, right capabilities
{
	left.Set(leftstick*conthrottle); //left is now set to left
	right.Set(rightstick*conthrottle/(-1));//right now goes right, -1 has significance because it discerns 
	//different movements of the joysticks to have diffrent movements of the robot
}
void TankDriveThrottle::throttle(float othrottle)//adjusts the throttle to a no throttle value
{
	conthrottle=othrottle; //we created a throttle that used to have values 0f -1 to 1 to now just 0 to 1
}							//^^this was just the meticulous math we used to get to that result
