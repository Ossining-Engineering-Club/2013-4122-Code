#include "ussensor.h"
#include "WPILib.h"

USSensor::USSensor(UINT32 channel):
	uschannel(channel)
{
	averagerange=0.0;
}

void USSensor::getsample(void)
{
	averagerange=0.9*averagerange+0.1*8.503*uschannel.GetVoltage();
}

float USSensor::getrange(void)
{
	averagerange =0.9*averagerange+0.1*8.503*uschannel.GetVoltage();
	return averagerange;
}

void USSensor::setscale(float scale)
{
	feetpervolt=scale;
}
