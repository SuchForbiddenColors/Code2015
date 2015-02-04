#include "WPILib.h"

class Wheelz
{
protected:
	RobotDrive* wheels;
	Encoder *encoder1;


public:
	Wheelz(int leftMotor, int rightMotor, int aChannel, int bChannel);

	void XDrive(GenericHID * XStick);
	void CarefulDrive(GenericHID * XStick);
	void DissectedDrive(float forward, float turn);

	float GetEncoder();
	bool GetDirectionEncoder();
	void TurnEncoder(float rotations, float leftSpeed, float rightSpeed); //TODO: Assign numbered encoders to motors, just spin specific ones

	void InitWatchdog(bool is);
	void SetExpiration(float exp);  // XXX: This is used as a warning comment.
								   // Yeah, SetExpiration doesn't do anything.
};
