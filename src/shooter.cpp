#include "shooter.h"
#include "constants.h"
#include "WPILib.h"
#include <math.h>

Shooter::Shooter(UINT32 forwardchannel, UINT32 backchannel, UINT32 armchannel, UINT32 heightchannel, UINT32 potchan):
	spinforward(forwardchannel),
	spinbackward(backchannel),
	shootarm(armchannel),
	shootangle(heightchannel),
	pospot(potchan)
{
	speed=0.0;
	ratio=initspinnerratio;	//Ratio of back spinner speed to front

}

void Shooter::spinnerson()
{
	spinforward.Set(speed);
	spinbackward.Set(ratio*speed);
}

void Shooter::spinnersoff()
{
	spinforward.Set(0.0);
	spinbackward.Set(0.0);
}

void Shooter::settarget()
{
	
}

void Shooter::shootarmstop()
{
	shootarm.Set(0.0);
}

void Shooter::spinspeed(float inspeed, float inratio)
{
	speed=inspeed;
	ratio=inratio;
	spinforward.Set(speed);
	spinbackward.Set(ratio*speed);
}

void Shooter::shoot()
{
	shootarm.Set(shootarmforwardspeed);
}

// Only use for Autonomous, where Robot does not need to drive
void Shooter::shootmultiple(int frisbeecount)
{
	for (int i = 0 ; i < frisbeecount; ++i) 			// Shoot 4 frisbees in Autonomous Mode
	{
		shootarm.Set(shootarmforwardspeed);		//Shoot a frisbee
		Wait(shootforwardtime);					//Wait for the arm to go fully forward
		shootarm.Set(-1.0*returnarmspeed);				//Pull the arm back
		Wait(shootbacktime);				//Wait for the arm to go back to position
		shootarm.Set(0.0);
		if(i<(frisbeecount-1)) Wait(droptime);					//Wait for next frisbee to drop
	}
}

void Shooter::returnarm()
{
	shootarm.Set(-1.0*returnarmspeed);
}
float Shooter::setangle(float changeangle)
{
	float saspeed;
	//saspeed=0;
	//if(pospot.GetVoltage()-changeangle>anglegain)shootangle.Set(anglespeed);
	//else if(changeangle-pospot.GetVoltage()>anglegain)shootangle.Set(-anglespeed);
	//else 
	saspeed=1.5*(pospot.GetVoltage()-changeangle);
	if(saspeed>=saspeedmax) saspeed=saspeedmax;
	if (saspeed<=-1*saspeedmax) saspeed=-1*saspeedmax;
	shootangle.Set(saspeed);
	return pospot.GetVoltage();
}
