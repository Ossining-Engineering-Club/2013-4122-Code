#include "LaserFrisbee.h"
#include "WPILib.h"
rangefrisbee::rangefrisbee()
{
	//initialize table
	distable[0][0]=7;//dist1 change it
	distable[0][1]=.7;//angle1 change it
	distable[0][2]=.8;
	distable[1][0]=16;//dist1 change it
	distable[1][1]=.7;//angle1 change it
	distable[1][2]=.8;
	distable[2][0]=21;//dist1 change it
	distable[2][1]=2.6;//angle1 change it
	distable[2][2]=.9;
	distable[3][0]=25;//dist1 change it
	distable[3][1]=4.23;//angle1 change it
	distable[3][2]=.9;
	distable[4][0]=35;//dist1 change it
	distable[4][1]=3.5;//angle1 change it
	distable[4][2]=1;
	distable[5][0]=45;//dist1 change it
	distable[5][1]=4.8;//angle1 change it
	distable[5][2]=1;
	distable[6][0]=55;//dist1 change it
	distable[6][1]=4.8;//angle1 change it
	distable[6][2]=1;
	//we wont need the distances to be equidistant
	//presort table low dist to high dist so that we can search it easily
	//
	distance=1;
	angle=1;
}
float rangefrisbee::getDistance(float anglein)
{
	int counter;
	angle=anglein;
	float weighting;
	counter=0;
	//find where distance is greater than dist. on table
	while(angle<distable[counter][1] && counter<distpoints)counter++;
	if(counter==0)counter++;
	if(counter==distpoints)counter--;
	//figuring out how close we are to each dist point, basically %error
	weighting=(angle-distable[counter-1][1])/(distable[counter][1]-distable[counter-1][1]);
	//shooting angle based on the two distance data points between which shooter lies
	//we weight each one based on how close the distance is to each using above %change formula thing
	distance=distable[counter-1][0]*(1-weighting)+distable[counter][0]*weighting;
	return distance;
}
float rangefrisbee::getAngle(float dist)
{
	int counter;
	float weighting;
	counter=0;
	distance=dist;
	//find where distance is greater than dist. on table
	while(distance>distable[counter][0] && counter<distpoints)counter++;
	if(counter==0)counter++;
	if(counter==distpoints)counter--;
	//figuring out how close we are to each dist point, basically %error
	weighting=(distance-distable[counter-1][0])/(distable[counter][0]-distable[counter-1][0]);
	//shooting angle based on the two distance data points between which shooter lies
	//we weight each one based on how close the distance is to each using above %change formula thing
	angle=distable[counter-1][1]*(1-weighting)+distable[counter][1]*weighting;
	return angle;
}
float rangefrisbee::getSpeed()
{
		int counter;
		float weighting;
		counter=0;
		//find where distance is greater than dist. on table
		while(distance>distable[counter][0] && counter<distpoints)counter++;
		if(counter==0)counter++;
		if(counter==distpoints)counter--;
		//figuring out how close we are to each dist point, basically %error
		weighting=(distance-distable[counter-1][0])/(distable[counter][0]-distable[counter-1][0]);
		//shooting angle based on the two distance data points between which shooter lies
		//we weight each one based on how close the distance is to each using above %change formula thing
		speed=distable[counter-1][2]*(1-weighting)+distable[counter][2]*weighting;
		return speed;
}
