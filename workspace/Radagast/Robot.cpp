#include "WPILib.h"
//#include "Wheelz.h"
//#include "Pneumatics.h" //We get them from Dash now
#include "Defines.h"
#include "Math.h"
#include "Dash.h"

using namespace std;

/* The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code, if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	Wheelz *wheels;
	Pneumatics *air;
	BuiltInAccelerometer *excel;
	CameraServer *camera;
	Vision *sight;
	Dash * dash;
	Elevator *rise;
	Timer *time;
	Joystick *XStick;
	Victor *testMotor;

public:
	Robot()
	{
		wheels = new Wheelz(MOTOR_DRIVE_LEFT, MOTOR_DRIVE_RIGHT, ENCODER_CHANNEL_A, ENCODER_CHANNEL_B, ENCODER_CHANNEL_C, ENCODER_CHANNEL_D);
		XStick = new Joystick(XSTICK_PORT);
		air = new Pneumatics();
		excel = new BuiltInAccelerometer();
		camera = CameraServer::GetInstance();
		sight = new Vision();
		rise = new Elevator(MOTOR_LIFT_CHANNEL, STRING_POTENTIOMETER_CHANNEL, UPPER_LIMIT_CHANNEL, LOWER_LIMIT_CHANNEL);
		dash = new Dash(wheels, air, excel, XStick, rise);
		time = new Timer();
		testMotor = new Victor(TEST_MOTOR_CHANNEL);

		wheels->SetExpiration(.5);
	}


	void Autonomous()
	{


	}



	void OperatorControl()
	{

		//wheels->InitWatchdog(true); //TODO: Doesn't work; kinda need it.

		bool driveCareful = false;
		bool elevatorTesting = false;
		bool driveX = true;

		float heightErrorBound = 1;
		float heightSlowBound = 4;
		dash->LiftHeight(0);
		float goalHeight = dash->currentHeight;

		time->Stop(); time->Reset();

		//sight->StartImageAcquisition();

		while (IsOperatorControl() && IsEnabled())
		{

			//Analyzing previous loop

			dash->AddEnergyToTotal(time->Get());
			dash->SetEncoderDistance();

			//How's My Driving?

			if(elevatorTesting)
			{
				rise->ManualLift(XStick->GetRawAxis(1) * -1); //1 is a controller's LeftY axis
													//No idea why, but forward gives negative numbers
				dash->PutString(1, "Testing Elevator");
			}
			else
			if(driveCareful)
			{
				wheels->CarefulDrive(XStick);
				dash->PutString(1, "Careful Driving");
			}
			else
			if(driveX)
			{
				wheels->XDrive(XStick);
				dash->PutString(1, "Normal Driving");
			}

			time->Stop();
			time->Reset();
			time->Start();

			//Dashboard functions

			dash->EncoderCount(1, 1); //Read the percentage of rotations of encoder1 on slider 1 //Works

			dash->EncoderCount(2, 2);

			//dash->PutNumber(2, wheels->GetEncoder(1));  //TODO: obsolete PutNumber/String

			dash->Acceleration(3, 3); //Read Z acceleration on slider 3

			dash->LiftHeight(4);

			//dash->DistancePerEnergy(4); //Read distance/energy ratio on slider 4

			dash->LimitSwitch(1, 1);  //Read top limit switch value on button 1

			dash->LimitSwitch(2, 2);

			dash->SolenoidPair(2, 1); //Read solenoid pair values on line 2

			//sight->DrawOval();

			sight->PutImage();

			//The Shift-Specific Functions

			dash->PutString(6, "Shift: None"); //Will be trumped by any other shift info

			if(XStick->GetRawButton(X_LEFT_BUMPER))
			{						//How's My Driving functions
				dash->PutString(6, "Shift: Driving Style");

				if(dash->StickyPress('a'))
				{
					driveX = true;
					driveCareful = false;
					elevatorTesting = false;
				}

				if(dash->StickyPress('x'))
				{
					driveCareful = true;
					driveX = false;
					elevatorTesting = false;
				}

				if(dash->StickyPress('y'))
				{
					elevatorTesting = true;
					driveX = false;
					driveCareful = false;
				}
			}

			if(XStick->GetRawButton(X_LEFT_CLICK))
			{						//Elevator functions
				dash->PutString(6, "Shift: Elevator");

				if(dash->StickyPress('a'))
				{
					goalHeight = 8; //Grab from ground
				}

				if(dash->StickyPress('b'))
				{
					goalHeight = 26; //Place on one
				}

				if(dash->StickyPress('x'))
				{
					goalHeight = 38; //Place on two
				}

				if(dash->StickyPress('y'))
				{
					goalHeight = 50; //Place on three
				}

				if(dash->StickyPress('r'))
				{
					dash->LiftHeight(12); //Give dummie number to just reset height value
					goalHeight = dash->currentHeight;
				}
			}

			if(fabs(dash->currentHeight - goalHeight) > heightErrorBound)
			{
				float speedReduction = 1;

				if(fabs(dash->currentHeight - goalHeight) < heightSlowBound)
				{
					speedReduction = 2;
				}
				else
				{
					speedReduction = 1;
				}

				if((dash->currentHeight - goalHeight) > 0)
				{
					rise->ManualLift(-.8 / speedReduction);
					     //Limit Switches accounted for in ManualLift()
				}
				else
				{
					rise->ManualLift(.8 / speedReduction);
				}
			}
			else
			{
				rise->ManualLift(0);
			}

			if((XStick->GetRawButton(X_LEFT_CLICK) || XStick->GetRawButton(X_LEFT_BUMPER) || XStick->GetRawButton(X_BACK)) == false)
			{
				if(dash->StickyPress('a'))
				{
					air->SolenoidFlip(1);
					air->SolenoidFlip(2);
				}

				if(dash->StickyPress('b'))
				{
					air->SolenoidFlip(3);
					air->SolenoidFlip(4);
				}
			}

			//Encoder Functions

			/*if(XStick->GetRawButton(X_Y))
			{
				if(XStick->GetRawButton(X_LEFT_BUMPER))
				{
					wheels->TurnEncoder(-2, .6, .6);
				}
				else {wheels->TurnEncoder(2, .6, .6);}
			}*/

			Wait(0.005);				// wait for a motor update time
		}
		//sight->StopImageAcquisition();
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
