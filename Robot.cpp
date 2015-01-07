#include "WPILib.h"
#include "Wheelz.h"
#include "Defines.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	Wheelz *wheels;
	Joystick *XStick;

public:
	Robot()
	{
		wheels = new Wheelz(MOTOR_DRIVE_LEFT, MOTOR_DRIVE_RIGHT);
		XStick = new Joystick(XSTICK_PORT);

		wheels->SetExpiration(.5);
	}


	void Autonomous()
	{


	}



	void OperatorControl()
	{
		wheels->InitWatchdog(true);
		while (IsOperatorControl() && IsEnabled())
		{
			wheels->XDrive(XStick);
			SmartDashboard::PutString("DB/String 0", "Explosions");
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
