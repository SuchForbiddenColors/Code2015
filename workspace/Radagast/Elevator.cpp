#include "Elevator.h"
#include "Defines.h"

Elevator::Elevator(int liftMotorPort, int upperLimitSwitchPort, int lowerLimitSwitchPort)
{
	liftMotor = new Victor(liftMotorPort);
	upperLimit = new DigitalInput(upperLimitSwitchPort);
	lowerLimit = new DigitalInput(lowerLimitSwitchPort);
}

void Elevator::ManualLift(float speed)
{
	if(speed > 1)
	{speed = 1;}

	if(speed < -1)
	{speed = -1;}

	if(upperLimit->Get() == UPPER_LIMIT_SWITCH_UNPRESSED && speed > 0)
	{
		liftMotor->Set(speed);
	}
	else
	{
		liftMotor->Set(0);
	}

	if(lowerLimit->Get() == LOWER_LIMIT_SWITCH_UNPRESSED && speed < 0)
	{
		liftMotor->Set(speed);
	}
	else
	{
		liftMotor->Set(0);
	}
}
