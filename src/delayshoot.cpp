#include "delayshoot.h"
#include "constants.h"
#include "WPILib.h"

AutoDelay::AutoDelay(UINT32 channel):
	uschannel(channel)
{

}

float AutoDelay::getsample(void)
{
	delaytime=autodelayscale*(5-uschannel.GetVoltage());
	return delaytime;
}

