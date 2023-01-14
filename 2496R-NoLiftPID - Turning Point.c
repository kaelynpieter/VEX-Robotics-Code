#pragma config(Sensor, dgtl1,  wolverine,      sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  lift,           sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  rquad,          sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  lquad,          sensorQuadEncoder)
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           left1,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           left2,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           left3,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           liftr,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           liftl,         tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           right1,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           right2,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           right3,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        					 This is Team 2496R's Version 1 Code                     */
/*        					   Important Lift Information Below:                     */
/*                              Lift1=Normal                                 */
/*                              Lift2=Reversed                               */
/*                              Lift3=Normal                                 */
/*                              Lift4=Reversed                               */
/*---------------------------------------------------------------------------*/


#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
/*---------------------------------------------------------------------------*/
/*                          Integers Named Below                             */
/*---------------------------------------------------------------------------*/
//Lift Values
int maxheight = 510;
int smallpostheight = 268;
int tallpostheight = 386;
float liftkP = 3.1;
float liftkI = 0.07;
float liftkD = 0.04;
int errorlift = 0;
int lastlifterror = 0;
int liftgoal = -15;
int powerlift =  0;
int cumerrorlift = 0;
int derivativelift = 0;
bool pidStatusLift = true;

//Intake
float intakekP = 2.1;
float intakekI = 0.1;
float intakekD = 0.12;
int error = 0;
int lasterror = 0;
int intakegoal = 0;
int power =  0;
int cumerror = 0;
int derivative = 0;
bool pidStatusClaw = true;
int position =0;
//Chassis
float oneinch = 22.88;
float onedegree = 1.28;


void unfold()
{
	while(SensorValue[wolverine] < 7)
	{
		motor[intake] = 20;
	}
	motor[intake] = 0;
	while(SensorValue[wolverine] > -74)
	{
		motor[intake] = -40;
	}
	motor[intake] = -10;
	wait(0.1);
	motor[intake] = 0;
	SensorValue[wolverine] = 0;

}
void drive(int speed, int goal)
{
	//Reset Motor Encoders
	SensorValue[lquad] = 0;
	SensorValue[rquad] = 0;
	motor[liftl] = 15;
	motor[liftr] =15;
	while(abs(SensorValue[rquad]) < (oneinch * goal)  && abs(SensorValue[lquad]) < (oneinch * goal))
	{
		motor[left1] = speed;
		motor[left2] = speed;
		motor[left3] = speed;
		motor[right1] = speed;
		motor[right2] = speed;
		motor[right3] = speed;

	}
	motor[left1] = -15;
	motor[left2] = -15;
	motor[left3] = -15;
	motor[right1] = -15;
	motor[right2] = -15;
	motor[right3] = -15;
	wait(0.1);
	motor[left1] = 0;
	motor[left2] = 0;
	motor[left3] = 0;
	motor[right1] = 0;
	motor[right2] = 0;
	motor[right3] = 0;
	motor[liftl] =0;
	motor[liftr] = 0;
	wait(0.05);
}
void turn(int speed1, int degree)// Left is positive and right is negative
{
	SensorValue[lquad] = 0;
	SensorValue[rquad] = 0;
	while(abs(SensorValue[rquad]) < (degree * onedegree)  && abs(SensorValue[lquad]) < (degree * onedegree))
	{
		motor[left1] = -speed1;
		motor[left2] = -speed1;
		motor[left3] = -speed1;
		motor[right1] = speed1;
		motor[right2] = speed1;
		motor[right3] = speed1;
	}
	motor[left1] = -15;
	motor[left2] = -15;
	motor[left3] = -15;
	motor[right1] = -15;
	motor[right2] = -15;
	motor[right3] = -15;
	wait(0.1);
	motor[left1] = 0;
	motor[left2] = 0;
	motor[left3] = 0;
	motor[right1] = 0;
	motor[right2] = 0;
	motor[right3] = 0;
	wait(0.05);
}
void redcap()
{
	unfold();
	motor[liftl] = -10;
	motor[liftr] = -10;
	drive(120, 40);
	drive(-40, 43);
	wait(1);
	drive(50, 29);
	turn(-70, 59);
	wait(0.1);
	drive(70, 34);
}
void bluecap()
{
	unfold();
	motor[liftl] = -10;
	motor[liftr] = -10;
	drive(120, 40);
	drive(-40, 43);
	wait(1);
	drive(50, 29);
	turn(70, 59);
	wait(0.1);
	drive(70, 34);
}
void rednet()
{
	unfold();
	motor[liftl] = -10;
	motor[liftr] = -10;
	drive(120, 40);
	turn(-70, 90);
	wait(0.1);
	drive(-70, 48);
	wait(0.1);
	drive(70, 48);
}
void bluenet()
{
	unfold();
	motor[liftl] = -10;
	motor[liftr] = -10;
	drive(120, 40);
	turn(70, 90);
	wait(0.1);
	drive(-70, 48);
	wait(0.1);
	drive(70, 48);
}
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


task autonomous()
{
	//Kaelyn, in autonmous you need to set the wolverine intake up for driving
	//and you need to set the position value at the end
	SensorValue[wolverine] =0;
	SensorValue[lift] =0;
	SensorValue[rquad] =0;
	SensorValue[lquad] =0;
	SensorValue[lquad] = 0;
	SensorValue[rquad] = 0;



}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
task clawPID()
{
	SensorValue[wolverine] = 0;
	while(true)
	{
		if(pidStatusClaw == true)
		{
			lasterror = error;
			error = intakegoal-SensorValue[wolverine];
			if(abs(error)<36)
			{
				cumerror = cumerror + error;
			}
			else if(abs(error) > 100)
			{
				cumerror = 0;
			}
			derivative = (error - lasterror);
			power = (error*intakekP) + (cumerror*intakekI) + (derivative*intakekD);
			motor[intake] = power;
			waitInMilliseconds(15);
		}
	}
}

task liftPID()
{
	SensorValue[lift] = 0;
	while(true)
	{
		if(pidStatusLift == true)
		{
			lastlifterror = errorlift;
			errorlift = liftgoal-SensorValue[lift];
			if(abs(errorlift)<36)
			{
				cumerrorlift = cumerrorlift + errorlift;
			}
			else if(abs(errorlift) > 100)
			{
				cumerrorlift = 0;
			}
			derivativelift = (errorlift - lastlifterror);
			powerlift = (errorlift*liftkP) + (cumerrorlift*liftkI) + (derivativelift*liftkD);
			motor[liftl] = powerlift;
			motor[liftr] = powerlift;
			waitInMilliseconds(15);
		}
	}
}


task usercontrol()
{
	SensorValue[wolverine] =0;
	SensorValue[lift] =0;
	SensorValue[rquad] =0;
	SensorValue[lquad] =0;
	startTask(clawPID);
	while(true)
	{
		//Chassis Code: Tank Drive
		motor[left1] = vexRT[Ch3]*3/4;
		motor[left2] = vexRT[Ch3]*3/4;
		motor[left3] = vexRT[Ch3]*3/4;
		motor[right1] = vexRT[Ch2]*3/4;
		motor[right2] = vexRT[Ch2]*3/4;
		motor[right3] = vexRT[Ch2]*3/4;

		//Lift Code: 6U goes up, 6D does down
		if(vexRT[Btn6U] == 1)
		{
			motor[liftl] = 120;
			motor[liftr] = 120;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[liftl] = -60;
			motor[liftr] = -60;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[liftl] = -15;
			motor[liftr] = -15;
		}
		else
		{
			motor[liftr] = 0;
			motor[liftl] = 0;
		}

		//Intake Code: 5U turns
		if(vexRT[Btn5U] == 1 )
		{
			if(pidStatusClaw == true)
			{
				if(position == 0)
				{
					intakegoal = 180;
					while(vexRT[Btn5U] == 1)
					{
						position = 1;
					}
				}
				else if(position == 1)
				{
					intakegoal = 0;
					while(vexRT[Btn5U] == 1)
					{
						position = 0;
					}
				}
			}
			else
			{
				motor[intake] = 70;
			}
		}
		else
		{
			if(pidStatusClaw == false)
			{
				motor[intake] = 0;
			}
		}

		//PID control for both Lift and Intake
		if(vexRT[Btn8U] == 1)
		{
			if(pidStatusClaw == true)
			{
				pidStatusClaw = false;
			}
			else if(pidStatusClaw == false)
			{
				pidStatusClaw = true;
			}
		}
		else{}
		if(vexRT[Btn8R] == 1)
		{
			SensorValue[wolverine] = 0;
		}
		else{}

	}
}