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
	Timer *time;
	Joystick *XStick;
	Victor *testMotor;

public:
	Robot()
	{
		wheels = new Wheelz(MOTOR_DRIVE_LEFT, MOTOR_DRIVE_RIGHT, ENCODER_CHANNEL_A, ENCODER_CHANNEL_B);
		XStick = new Joystick(XSTICK_PORT);
		air = new Pneumatics();
		excel = new BuiltInAccelerometer();
		camera = CameraServer::GetInstance();
		sight = new Vision();
		dash = new Dash(wheels, air, excel, XStick);
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
		dash->PutString(1, "Relinquished");

		bool testHasBeenPressed = false;
		bool flipOneHasBeenPressed = false;
		bool flipTwoHasBeenPressed = false;
		bool changeHasBeenPressed = false;

		bool driveCareful = false;

		time->Stop(); time->Reset();

		dash->PutString(6, dash->GetString(5));

		sight->StartImageAcquisition();

		while (IsOperatorControl() && IsEnabled())
		{

			//How's My Driving?

			if(driveCareful)
			{
				wheels->CarefulDrive(XStick);
			}
			else
			{
				wheels->XDrive(XStick);
			}

			//Dashboard functions

			dash->EncoderCount(1); //Read the percentage of rotations on slider 1 //Works

			dash->PutNumber(2, wheels->GetEncoder());  //TODO: obsolete PutNumber/String as public functions, move them to private

			dash->Acceleration(3, 2); //Read Y acceleration on slider 3

			dash->Acceleration(4, 3); //Read Z acceleration on slider 4

			//sight->DrawOval();

			sight->PutImage();

			//The HasBeenPressed's //TODO: You still can probably make a function for this

			if(XStick->GetRawButton(X_A) && flipOneHasBeenPressed == false)
			{
				flipOneHasBeenPressed = true;
				air->SolenoidFlip(1);
			}

			if(XStick->GetRawButton(X_B) && flipTwoHasBeenPressed == false)
			{
				flipTwoHasBeenPressed = true;
				air->SolenoidFlip(2);
			}

			if(XStick->GetRawButton(X_A) == false)
			{
				flipOneHasBeenPressed = false;
			}

			if(XStick->GetRawButton(X_B) == false)
			{
				flipTwoHasBeenPressed = false;
			}

			if(dash->StickyPress('x'))
			{
				if(driveCareful == true)
				{
					driveCareful = false;
				}
				else if(driveCareful == false)
				{
					driveCareful = true;
				}
			}

			/*if(XStick->GetRawButton(X_X) && changeHasBeenPressed == false)
			{
				changeHasBeenPressed = true;
				if(driveCareful == true)
				{
					driveCareful = false;
				}
				else if(driveCareful == false)
				{
					driveCareful = true;
				}
			}

			if(XStick->GetRawButton(X_X) == false)
			{
				changeHasBeenPressed = false;
			}*/

			/*if(XStick->GetRawButton(X_X))
			{
				testHasBeenPressed = true;
			}
			else
			{
				testHasBeenPressed = false;
			}

			if(testHasBeenPressed) //Works
			{
				time->Start();
				float speed;
				speed = time->Get() / 3; //Time returns in seconds

				if(speed > 1)
				{speed = 1;}

				testMotor->Set(speed);
			}
			else
			{
				time->Stop();
				time->Reset();
				testMotor->Set(0);
			}*/


			//Encoder Functions

			if(XStick->GetRawButton(X_Y))
			{
				if(XStick->GetRawButton(X_LEFT_BUMPER))
				{
					wheels->TurnEncoder(-2, .6, .6);
				}
				else {wheels->TurnEncoder(2, .6, .6);}
			}

			Wait(0.005);				// wait for a motor update time
		}
		sight->StopImageAcquisition();
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
