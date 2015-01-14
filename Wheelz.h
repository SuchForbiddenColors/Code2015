#include "WPILib.h"

class Wheelz
{
protected:
	RobotDrive* wheels;
	Encoder *encoder;


public:
	Wheelz(int leftMotor, int rightMotor, int aChannel, int bChannel);

	void XDrive(GenericHID * XStick);
	void CarefulDrive(GenericHID * XStick);
	void DissectedDrive(float forward, float turn);

	float GetEncoder();
	bool GetDirectionEncoder();
	void EncoderTurn(float rotations, Victor *testMotor);

	void InitWatchdog(bool is);
	void SetExpiration(float exp);

};

