
/*
 * 
 * Constants for Autonomous Mode
 */
#define autospeed				0.8		//Speed of Front Spnner for Autonomous Mode
#define autospinnerratio		0.8		//Ratio of speeds for autonomous Mode
#define autonumber				3		//Number of frisbees shot in Autonomous Mode
#define autodelayscale			1.65		//scales anolog input of time delay

//Time Constants
#define waittime 				0.01	//Time in seconds for wait in each fast loop
#define shootforwardtime		0.19	//Time in seconds to allow Shoot arm to move completely forward
#define shootbacktime			0.25	//Time in seconds for shooting arm to go back
#define droptime				0.5		//Time in seconds to frisbee to drop before shooting
#define fullspinuptime 			3.0  	//Time in seconds for spinners to fully spin up to speed
#define dunkwaittime 			0.5		//Time in seconds to wait for spinup on dunk on pyramid
#define dunknumber				4		//Number to dunk

#define dunkspinspeed 			0.3		//Spinner Speed for dunking
#define initspinnerratio		0.8		//Starting Ratio of back Spinner Speed to front

#define	shootarmforwardspeed	1.0		//Speed to move arm forward when shooting
#define	returnarmspeed			0.6		//speed to move arm back when shooting
#define trimdelta				4		//Move the tarrget line 5 pixels per click

#define anglescale				0.5		//Scale for angle adjust
#define minanglestick			0.1		//Ignore joystick movements less than this for angle changes
#define lowangle .7
#define highangle 4.8

/*
 * Good Values
 * 
#define autospeed				0.4		//Speed of Front Spnner for Autonomous Mode
#define autospinnerratio		0.8		//Ratio of speeds for autonomous Mode
#define autonumber				3		//Number of frisbees shot in Autonomous Mode

//Time Constants
#define waittime 				0.01	//Time in seconds for wait in each fast loop
#define shootforwardtime		0.16	//Time in seconds to allow Shoot arm to move completely forward
#define shootbacktime			0.35	//Time in seconds for shooting arm to go back
#define droptime				0.5		//Time in seconds to frisbee to drop before shooting
#define fullspinuptime 			3.0  	//Time in seconds for spinners to fully spin up to speed
#define dunkwaittime 			0.5		//Time in seconds to wait for spinup on dunk on pyramid
#define dunknumber				4		//Number to dunk

#define dunkspinspeed 			0.3		//Spinner Speed for dunking
#define initspinnerratio		0.8		//Starting Ratio of back Spinner Speed to front

#define	shootarmforwardspeed	1.0		//Speed to move arm forward when shooting
#define	returnarmspeed			0.6		//speed to move arm back when shooting
#define trimdelta				4		//Move the tarrget line 5 pixels per click

#define anglescale				0.5		//Scale for angle adjust
#define minanglestick			0.1		//Ignore joystick movements less than this for angle changes
*/
#define anglegain .25
#define anglespeed .3
#define saspeedmax .8
