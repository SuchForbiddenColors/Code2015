#include "WPILib.h"

class Elevator
{
protected:
	Victor *liftMotor;

public:
	DigitalInput *upperLimit;
	DigitalInput *lowerLimit;
	AnalogPotentiometer *stringPot;

	Elevator(int liftMotorPort, int stringPotPort, int upperLimitSwitchPort, int lowerLimitSwitchPort);
	void ManualLift(float speed);
};
