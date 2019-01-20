#include "climber.h"
#include "WPILib.h"
Climber::Climber(UINT32 arm, UINT32 cable):
	Arm(arm),
	Cable(cable)
{
	mode=true;
}
void Climber::climbAllow(bool button)
{
	if(button==true)
	{
	modeAssist=true;
	}
	if (modeAssist==true and button==false)
	{
		if (mode==false)
		{
			mode=true;
		}
		else {mode=true;}
		
	}
	if(mode==false)
	{
	Cable.Set(0);
	Arm.Set(0);
	}
}
void Climber::cableAdjust(float Stick)
{
	Cable.Set(-1.0*Stick);
}
void Climber::armAdjust(float Stick)
{	
	Arm.Set(Stick);
}
//char *Climber4122::do(drugs)
//{
//	I get high;
//	I get High;
//	YEEAAAAAH;
//	if(it's been a hard day's night);
//  {return "i've been working like a dog";}
//  else
//  {return "i should be sleeping like a log";}
//}
