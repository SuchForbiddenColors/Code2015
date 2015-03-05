#include "Elevator.h"
#include "Defines.h"

Elevator::Elevator(int liftMotorPort, int stringPotPort, int upperLimitSwitchPort, int lowerLimitSwitchPort)
{
	liftMotor = new Victor(liftMotorPort);
	stringPot = new AnalogPotentiometer(stringPotPort, 50, 0);
	upperLimit = new DigitalInput(upperLimitSwitchPort);
	lowerLimit = new DigitalInput(lowerLimitSwitchPort);
}

void Elevator::ManualLift(float speed)
{
	if(speed > 1)
	{speed = 1;}

	if(speed < -1)
	{speed = -1;}

	float motorInput;

	motorInput = ELEVATOR_MOTOR_INVERT * speed;

	if(speed > 0)
	{
		if(upperLimit->Get() == UPPER_LIMIT_SWITCH_UNPRESSED)
		{
			liftMotor->Set(motorInput);
		}
		else
		{
			liftMotor->Set(0);
		}
	}

	if(speed < 0)
	{
		if(lowerLimit->Get() == LOWER_LIMIT_SWITCH_UNPRESSED)
		{
			liftMotor->Set(motorInput);
		}
		else
		{
			liftMotor->Set(0);
		}
	}

	if(speed == 0)
	{
		liftMotor->Set(0);
	}


}
