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
		dash = new Dash(wheels, air);
		time = new Timer();
		testMotor = new Victor(TEST_MOTOR_CHANNEL);

		wheels->SetExpiration(.5);
	}


	void Autonomous()
	{


	}



	void OperatorControl()
	{

		wheels->InitWatchdog(true);
		dash->PutString(1, "Relinquished");

		bool testHasBeenPressed;

		time->Stop(); time->Reset();

		string cat;
		cat = SmartDashboard::GetString("DB/String 5");
		SmartDashboard::PutString("DB/String 6", cat);  //This works!
		
		double rotationCount;

		while (IsOperatorControl() && IsEnabled())
		{

			wheels->CarefulDrive(XStick);

			rotationCount = wheels->GetEncoder() / ENCODER_ONE_PULSES_PER_REVOLUTION;
			rotationCount *= 100; // Make't a percentage

			dash->PutNumber(1, rotationCount);

			dash->PutNumber(2, wheels->GetEncoder());

			if(XStick->GetRawButton(X_A))
			{
				testMotor->Set(0);
			}

			if(XStick->GetRawButton(X_B))
			{
				air->SolenoidFlip(2);
			}

			if(XStick->GetRawButton(X_X))
			{
				testHasBeenPressed = true;
			}
			else
			{
				testHasBeenPressed = false;
			}

			if(testHasBeenPressed)
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
			}


			if(XStick->GetRawButton(X_Y))
			{
				if(XStick->GetRawButton(X_LEFT_BUMPER))
				{
					wheels->EncoderTurn(-2, testMotor);
				}
				else {wheels->EncoderTurn(2, testMotor);}
			}

			Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
