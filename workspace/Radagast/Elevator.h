#include "WPILib.h"

class Elevator
{
protected:
	Victor *liftMotor;

public:
	DigitalInput *upperLimit;
	DigitalInput *lowerLimit;

	Elevator(int liftMotorPort, int upperLimitSwitchPort, int lowerLimitSwitchPort);
	void ManualLift(float speed);
};
