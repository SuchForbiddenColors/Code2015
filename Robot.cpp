#include "WPILib.h"
//#include "Wheelz.h"
//#include "Pneumatics.h" //We get them from Dash now
#include "Defines.h"
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
	Joystick *XStick;

public:
	Robot()
	{
		wheels = new Wheelz(MOTOR_DRIVE_LEFT, MOTOR_DRIVE_RIGHT);
		XStick = new Joystick(XSTICK_PORT);
		air = new Pneumatics();
		dash = new Dash(wheels, air);

		wheels->SetExpiration(.5);
	}


	void Autonomous()
	{


	}



	void OperatorControl()
	{

		wheels->InitWatchdog(true);
		SmartDashboard::PutString("DB/String 0", "2Explosions");
		//Can't yet PutNumbers in

		string cat;
		cat = SmartDashboard::GetString("DB/String 5");
		SmartDashboard::PutString("DB/String 6", cat);  //This works!

		while (IsOperatorControl() && IsEnabled())
		{
			wheels->XDrive(XStick);

			if(XStick->GetRawButton(X_A))
			{
				air->SolenoidFlip(1);
			}

			if(XStick->GetRawButton(X_B))
			{
				air->SolenoidFlip(2);
			}

			if(XStick->GetRawButton(X_X))
			{
				air->SolenoidFlip(3);
			}

			if(XStick->GetRawButton(X_Y))
			{
				air->SolenoidFlip(4);
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
