#include "LaserInterface.h"
#include "WPILib.h"
#include "stdlib.h"
#include "string.h"
laserrange::laserrange():
	laser(19200)
{
	//laser.SetFlowControl();
	laser.SetFlowControl(SerialPort::kFlowControl_None);
	laser.Write("F\n",3);
	laser.Write("R\n",3);
}
float laserrange::getfeet()
{
	int numbytes;
	numbytes=laser.GetBytesReceived();
	if(numbytes>0)
	{
	laser.Read(laserout, numbytes);
	laser.Flush();
	laserstr=laserout;
	laserstr.erase(0,5);
	laserstr.erase(7,1);
	rawdist=laserstr.c_str();
	distance=atof(rawdist);
	}
	return distance;
	
}
char* laserrange::getraw()
{
	int numbytes;
	numbytes=laser.GetBytesReceived();
	if(numbytes>12)
	{
	laser.Read(laserout, numbytes);
	}
	return laserout;
}
