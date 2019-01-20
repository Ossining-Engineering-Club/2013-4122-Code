#ifndef LASERINTERFACE_H_
#define LASERINTERFACE_H_
#include "WPILib.h"
class laserrange
{
public:
	laserrange();
	float getfeet(void);
	char* getraw(void);
private:
	SerialPort laser;
	char* laserout;
	const char* rawdist;
	string laserstr;
	float distance;
};
#endif
