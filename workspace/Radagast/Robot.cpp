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
		wheels = new Wheelz(MOTOR_DRIVE_LEFT, MOTOR_DRIVE_RIGHT, ENCODER_CHANNEL_A, ENCODER_CHANNEL_B);
		XStick = new Joystick(XSTICK_PORT);
		air = new Pneumatics();
		excel = new BuiltInAccelerometer();
		camera = CameraServer::GetInstance();
		sight = new Vision();
		dash = new Dash(wheels, air, excel, XStick);
		rise = new Elevator(MOTOR_LIFT_CHANNEL, UPPER_LIMIT_CHANNEL, LOWER_LIMIT_CHANNEL);
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

		bool driveCareful = false;
		bool elevatorTesting = false;

		time->Stop(); time->Reset();

		sight->StartImageAcquisition();

		while (IsOperatorControl() && IsEnabled())
		{

			//Analyzing previous loop

			dash->AddEnergyToTotal(time->Get());
			dash->SetDistance();

			//How's My Driving?

			if(elevatorTesting)
			{
				rise->ManualLift(XStick->GetRawAxis(1)); //1 is a controller's LeftY axis
			}
			else
			if(driveCareful)
			{
				wheels->CarefulDrive(XStick);
			}
			else
			{
				wheels->XDrive(XStick);
			}

			time->Stop();
			time->Reset();
			time->Start();

			//Dashboard functions

			dash->EncoderCount(1); //Read the percentage of rotations on slider 1 //Works

			dash->PutNumber(2, wheels->GetEncoder());  //TODO: obsolete PutNumber/String as public functions, move them to private

			dash->Acceleration(3, 3); //Read Z acceleration on slider 3

			dash->DistancePerEnergy(4); //Read distance/energy ratio on slider 4

			//sight->DrawOval();

			sight->PutImage();

			//The HasBeenPressed's

			if(dash->StickyPress('a'))
			{
				air->SolenoidFlip(2);
			}

			if(dash->StickyPress('b'))
			{
				air->SolenoidFlip(2);
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

			if(dash->StickyPress('y'))
			{
				if(elevatorTesting == true)
				{
					elevatorTesting = false;
				}
				else if(elevatorTesting == false)
				{
					elevatorTesting = true;
				}
			}

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

				if(XStick->GetRawButton(X_LEFT_BUMPER))
				{testMotor->Set(-speed);}
				else
				{testMotor->Set(speed);}
			}
			else
			{
				time->Stop();
				time->Reset();
				testMotor->Set(0);
			}*/

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
