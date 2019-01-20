#include "WPILib.h"
#include "constants.h"
#include "shooter.h"
#include "climber.h"
#include "ussensor.h"
#include "tankdrivethrottle.h"
#include "HookSensor.h"
#include "LaserFrisbee.h"
#include "delayshoot.h"
#include "LaserInterface.h"
class RobotDemo : public SimpleRobot
{											//declarations, reserve variables and instances for later use
	Joystick stick1; 						//Shooter Joystick
	Joystick stick2; 						//Driver Right Joystick
	Joystick stick3;						//Driver Left Joystick
	TankDriveThrottle tankdrive;
	Shooter shooter;
	Climber climber;
	USSensor ranger;						//calls up an instance of ultrasonic sensor 
	HookSensor locksensor;
	laserrange laser;//detects whne the Robot is locked on the horizontal bar
	rangefrisbee converter;
	AutoDelay autodelay;
//	Drive Input Variables
	bool driveMode;							// When Driving or shooting, driveMode=1
	char *controlModeLabel; 				//String represnting Control mode
	float driveThrottle;					// Throttle value read from button
	int slowloopcount;
	
	
//	Shooter Variables
	enum shootstates {SpinUp, ShootReady, ShootArmForward, ShootArmBackward, DropNext, Off};
	shootstates shootstate;
	bool SpinnersOn;   			//Indicates spinners are running
	float spinThrottle; 		// Speed of fromt spinner
	float spinRatio;			// Ratio of Back Spinner speed to front
	float spinSpeedFront;		// Front Spinner Speed x100
	float spinSpeedBack;		// Back Spinnner Speed x100
	float rangeinfeet;
	int shotsqueued;			//Number of frisbees ready to be shot either by quick trigger pulls or dunking
    float shootEventTimer;		//Time after requesting shot
    float shootanglechange;		//Input for changing shoot angle
          
    
// Booleans that indicate buttons are pressed down
    bool shootPressed, ratioUpPressed, ratioDownPressed;
    bool trimShootUpPressed, trimShootDownPressed;

//laser
    enum lasermodes{manual, automatic, ps1, ps2, ps3};//ps stands for pre-set
    lasermodes lasermode;
    float printdist, printangle;
    int printdint;
    char * lasermodelabel;
public:
	RobotDemo(void):
		stick1(1),			// Declare in the same order as above
		stick2(2),
		stick3(3),
		tankdrive(1,2),
		shooter(3,4,7,8,5),
		climber(6,5),	 	// Set Jaguar numbers for (1) Rotating arms and (2 & 3) for Cable pulling
		ranger(1),          	// Set the analog channel for the ultrasonic ranger
		locksensor(2,3),		// Define the analog inputs for the Locking Sensor
		laser(),
		converter(),
		autodelay(4)
	{
	}

	void Autonomous(void)
	{
		DriverStationLCD*Lcd1=DriverStationLCD::GetInstance();	//Initialize Display device
		controlModeLabel="Autonomous Mode";
		shootstate=ShootReady;
		shotsqueued=0;
		spinSpeedFront=100*autospeed;
		spinRatio=autospinnerratio;
		spinSpeedBack=spinSpeedFront*spinRatio;
		Wait(autodelay.getsample());			//wait variable delay before delay
		shooter.spinspeed(autospeed,spinRatio);		//Set Spin speed and ratio of back/front speeds
		Lcd1->Clear();													//clears existing info
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line1, controlModeLabel);		//displays the controlMode
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line2, "Spinner 1 speed %f", spinSpeedFront);	//displays the spinner 1 speed
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line3, "Spinner 2 speed %f", spinSpeedBack);	//displays the spinner 2 speed
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line4, "Ratio %f", spinRatio);	//displays spinner 2 percentage of 1
		Lcd1->UpdateLCD();													//sends all the information to the driver station
		Wait(fullspinuptime);					//Wait for spinners to be up to speed	
		shooter.shootmultiple(autonumber);				//Shoot autonumber frisbees
		if(autonumber==3)controlModeLabel="3 Frisbeeds Shot";
		else controlModeLabel="3 Frisbeeds Shot";
		Lcd1->Clear();													//clears existing info
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line1, controlModeLabel);		//displays the controlMode
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line2, "Spinner 1 speed %f", spinSpeedFront);	//displays the spinner 1 speed
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line3, "Spinner 2 speed %f", spinSpeedBack);	//displays the spinner 2 speed
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line4, "Ratio %f", spinRatio);	//displays spinner 2 percentage of 1
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line5, " Delay %f", autodelay.getsample());
		Lcd1->UpdateLCD();			
	}
	void OperatorControl(void)
	{
		DriverStationLCD*Lcd1=DriverStationLCD::GetInstance();	//Initialize Display device
		SpinnersOn=0;
		shootstate=Off;//make off state, and add state
		//handle shoot spinup time in this state
		shootEventTimer=0;
		shotsqueued=0;
		spinRatio=initspinnerratio;
		driveMode=1;
		controlModeLabel="Mode 1: Drive";
		spinSpeedFront=0;
		spinSpeedBack=0;
		slowloopcount=0;
		shootPressed=0;
		ratioUpPressed=0;
		ratioDownPressed=0;
		trimShootUpPressed=0; 
		trimShootDownPressed=0;
		shooter.spinnersoff();
		tankdrive.drive(0.0,0.0);	// Stop the drive motors
		driveThrottle=(1-stick2.GetThrottle())/2;
		lasermode=manual;
		shootanglechange=1;
		
		
/*
 * 	Major Slow Loop: Gather data on Slow loop: Modes, Throttles, Ranges
 *          		              
 */	
	while (IsOperatorControl())
	{
		++slowloopcount;
/*
 * 	First Determine Operational Mode and change if needed: DriveMode or ClimbMode
 */
		if (stick2.GetRawButton(10) && !driveMode)	
		{
			driveMode=1;		
			controlModeLabel="Mode 1: Drive";				//Set the mode for later use in the display
			climber.armAdjust(0.0);							//Prevent the Climber arm from moving starting Tank Mode
			climber.cableAdjust(0.0);						//Prevent the Climber cable from moving when starting Tank Mode
		}
		else if (stick2.GetRawButton(11) && driveMode)		// Use else if, so only one mode will be used
		{
			driveMode=0;
			controlModeLabel="Mode 2: Climb";					//sets the variable for later use in the display
			SpinnersOn=0;
			shooter.spinnersoff();
			tankdrive.drive(0.0,0.0);	// Stop the drive motors
		}
/*
 * 	Process DriveMode in Slow Loop	
 */
		if(driveMode)
		{
			driveThrottle=(1-stick2.GetThrottle())/2;
			tankdrive.throttle(driveThrottle);
			
			//	Get Range in feet
			rangeinfeet=ranger.getrange();	 //Read the range in feet 	
			//	Handle Spinners On and Off Buttons and set the SpinnersOn flag appropriately
			if(!SpinnersOn && stick1.GetRawButton(4))       //If button 3 is pressed and spinners not on, turn them on
			{ 
				SpinnersOn=1; 
				shotsqueued=0;								//new feature
			}
			else if(SpinnersOn && stick1.GetRawButton(5))
			{ 
				SpinnersOn=0; 
				shooter.spinnersoff();
				spinSpeedFront=0;
				spinSpeedBack=0;
			}
			if(SpinnersOn)
			{	
				if(lasermode!=manual) spinThrottle=converter.getSpeed(); 
				else spinThrottle=(1-stick1.GetThrottle())/2;
				spinSpeedFront=100*spinThrottle;
				spinSpeedBack=spinSpeedFront*spinRatio;
				shooter.spinspeed(spinThrottle,spinRatio);	
			}
			if(stick1.GetRawButton(6))
			{
				if(!ratioUpPressed)
				{
					ratioUpPressed=1;
					spinRatio=spinRatio+.05;
					spinSpeedBack=spinSpeedFront*spinRatio*SpinnersOn;
				}
			}
			else if(ratioUpPressed) 
				ratioUpPressed=0;
			if(stick1.GetRawButton(7))
			{
				if(!ratioDownPressed)
				{
					ratioDownPressed=1;
					spinRatio=spinRatio-.05;
					spinSpeedBack=spinSpeedFront*spinRatio*SpinnersOn;
				}
			}
			else if(ratioDownPressed) 
				ratioDownPressed=0;	
		}		//End of Slow Loop DriveMode Actions
/*
 *         Execute Fast Loop for Responsiveness: Drive robot, Arm movements, Shooting
 */						
		for (int i = 0 ; i < 10; ++i) 						// Creates a loop which goes 10 times
		{
			Wait(waittime);								//Currently this will happen 100 times per second
/*
 *	Process Fast Events Common to DriveMode and ClimbModes
 */			
			shootEventTimer=shootEventTimer+waittime;		//Increment the time from the last shot
/*
 * Process Shooting State Machine
 * If the trigger is pulled, first queue the frisbee for shooting
 */
			if(stick1.GetRawButton(1))       		// If the trigger is pressed AND
			{
				if(!shootPressed)            	// If it is the first cycle that the Button has been depressed AND
				{
					shootPressed=1;				
					if(driveMode)				// If the Robot is in driveMode AND
					{	
						if(shotsqueued<4)		// And less than 4 frisbees have been queued, then queue another shot
							++shotsqueued;
					}
// Dunk Condition: Climb Mode and Shoot Trigger pressed						
					else
					{
						shotsqueued=dunknumber;
						shooter.spinspeed(dunkspinspeed,spinRatio);		//Set Spin speed and ratio of back/front speeds
						shootstate=SpinUp;
						SpinnersOn=1;
						shootEventTimer=0.0;
					}
				}
			}
			else if(shootPressed) 
					shootPressed=0;
		
// Shoot if a shot is queued, the spinners are on and the arm is ready or we have a dunk request and have waited for spinup
			if ((shootstate==ShootReady && shotsqueued>0 && SpinnersOn) 
					|| (shootstate==SpinUp && shootEventTimer>=dunkwaittime)) 
			{
				shooter.shoot();
				shootEventTimer=0.0;
				shootstate=ShootArmForward;	
				--shotsqueued;
			}
// Pull arm back when shootforward time is exceeded
			if (shootstate==ShootArmForward && shootEventTimer>=shootforwardtime) //Return arm after shoottime
			{
				shooter.returnarm();			
				shootstate=ShootArmBackward;
				shootEventTimer=0.0;
			}
// Set shoot arm to ready when it had gone fully back
			if (shootstate==ShootArmBackward && shootEventTimer>=shootbacktime)
			{
				shootstate=DropNext;
				shooter.shootarmstop();
				shootEventTimer=0.0;
			}   
// Set shoot arm to ready when it had gone fully back
			if (shootstate==DropNext && shootEventTimer>=droptime)
			{
				shootstate=ShootReady;
			}
//For when the spinners are off
			if (shootstate==Off)
			{
				if(SpinnersOn)//if the spinners are turned on, wait the spinup time, and then let robot shoot
					shootstate=SpinUp;
				
				else//if the spinners aren't turned on, reset the timer
					shootEventTimer=0.0;
			}
			if(shootstate==SpinUp && shootEventTimer>=fullspinuptime)
			{
				shootEventTimer=0.0;
				shootstate=ShootReady;
			}
				
				
//Make shootstate off when spinners killed
			if (shootstate==ShootReady && !SpinnersOn) 
			{
				shootstate=Off;
			}
/*
 * 	Process Fast Events for Drive Shoot
 */							
			if(driveMode)									//Choose what joysticks are used to control
			{
				tankdrive.drive(stick3.GetY(),stick2.GetY());
				if(stick1.GetRawButton(11)) lasermode=manual;
				if(stick1.GetRawButton(10)) lasermode=automatic;
				if(stick1.GetRawButton(2)) lasermode=ps1;
				if(stick1.GetRawButton(3)) lasermode=ps2;
				if(stick1.GetRawButton(6)) lasermode=ps3;
				switch (lasermode)
				{
				case manual:
					shootanglechange=stick1.GetY()*.01+shootanglechange;
					printangle=shooter.setangle(shootanglechange);
					if(shootanglechange>=highangle)shootanglechange=highangle;
					if(shootanglechange<=lowangle)shootanglechange=lowangle;
					printdist=converter.getDistance(shootanglechange);					
					lasermodelabel="MANUAL";
					break;
				case automatic:
					printdist=laser.getfeet();
					shootanglechange=converter.getAngle(printdist);
					shooter.setangle(shootanglechange);
					lasermodelabel="AUTO";
					lasermode=manual;
					break;
				case ps1:
					printdist=16;
					shootanglechange=converter.getAngle(printdist);
					shooter.setangle(shootanglechange);
					lasermodelabel="PYRAMID";
					break;
				case ps2:
					printdist=46;
					shootanglechange=converter.getAngle(printdist);
					shooter.setangle(shootanglechange);
					lasermodelabel="FULL COURT";
					break;
				case ps3:
					printdist=25;
					shootanglechange=converter.getAngle(printdist);
					shooter.setangle(shootanglechange);
					lasermodelabel="HALF COURT";
					break;
				}
			}
/*
 * 	Process Fast Events for ClimbMode
 */		
			else
			{	
				climber.armAdjust(stick2.GetY());			//sets the arm motor speed to the y-axis of the stick
				climber.cableAdjust(stick3.GetY());			//sets the cable motor speed to the y-axis of the stick
			}
	
			
		}	//stops the loop. It will repeat 6 times, then continue
/*    End of Fast Loop
 *    
 *    Back to Slow Loop: Display Data on LCD
 */
		printdint=(int)printdist;
		Lcd1->Clear();													//clears existing info
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line1, "%s,%s",controlModeLabel,lasermodelabel);		//displays the controlMode
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line6, "Spin1 %f, Spin2 %f", spinSpeedFront, spinSpeedBack);	//displays the spinner 1 speed
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line4, "delaytime %f", autodelay.getsample());	//displays the spinner 2 speed
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line2, "Dist %f", printdist);	//displays spinner 2 percentage of 1
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line5, "Shots %i, angle %f", shotsqueued,shootanglechange);	
		Lcd1->PrintfLine(DriverStationLCD::kUser_Line3, "Climb Status: %s", locksensor.getStatus());	//Display Bar Lock Status
		Lcd1->UpdateLCD();													//sends all the information to the driver station

		}	//End of the Slow Loop
	}		//End of OperatorControl
};			//End of Class

START_ROBOT_CLASS(RobotDemo);

