#include "WPILib.h"

class Wheelz
{
protected:
	RobotDrive* wheels;
	Encoder *encoder1;
	Encoder *encoder2;


public:
	float leftMotorInput;
	float rightMotorInput;

	Wheelz(int leftMotor, int rightMotor, int aChannel, int bChannel, int cChannel, int dChannel);

	void XDrive(GenericHID * XStick);
	void CarefulDrive(GenericHID * XStick);
	void DissectedDrive(float forward, float turn);

	float GetEncoder(int encoderNumber);
	float GetDistance(int encoderNumber);
	bool GetDirectionEncoder(int encoderNumber);
	void TravelForward(float distance, float speed);
	void TurnEncoder(float rotations, float leftSpeed, float rightSpeed); //TODO: Assign numbered encoders to motors, just spin specific ones

	void InitWatchdog(bool is);
	void SetExpiration(float exp);  // XXX: This is used as a warning comment.
								   // Yeah, SetExpiration doesn't do anything.
};
