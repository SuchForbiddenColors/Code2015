#include "WPILib.h"

class Wheelz
{
protected:
	RobotDrive* wheels;



public:
	Wheelz(int leftMotor, int rightMotor);
	void XDrive(GenericHID * XStick);
	void DissectedDrive(float forward, float turn);
	void InitWatchdog(bool is);
	void SetExpiration(float exp);

};
