#include "Wheelz.h"
#include "Defines.h"
#include "Math.h"

Wheelz::Wheelz(int leftMotor, int rightMotor)
{
	wheels = new RobotDrive(leftMotor, rightMotor);
}

void Wheelz::DissectedDrive(float forward, float turn)
{
	float leftSpeed, rightSpeed;
	float m_sensitivity = .5;

	if (turn < 0)
	{
		float value = log(-turn);
		float ratio = (value - m_sensitivity)/(value + m_sensitivity); //This is pre-existing library code
		if (ratio == 0) ratio =.0000000001;							  // I'm not familiar with its use, so just roll with it
			leftSpeed = forward / ratio;
			rightSpeed = forward;
	}
	else if (turn > 0)
	{
		float value = log(turn);
		float ratio = (value - m_sensitivity)/(value + m_sensitivity);
		if (ratio == 0) ratio =.0000000001;
			leftSpeed = forward;
			rightSpeed = forward / ratio;
	}
	else
	{
		leftSpeed = forward;
		rightSpeed = forward;
	}

	wheels->SetLeftRightMotorOutputs(leftSpeed, rightSpeed);
}

void Wheelz::XDrive(GenericHID *XStick)
{
	float forward = XStick->GetRawAxis(2); //2 is a controller's LeftY
	float turn = XStick->GetRawAxis(4); //4 is a controller's RightX
	float turbo = XStick->GetRawAxis(3); //3  either Trigger, but will only work if use Left Trigger, which
										//controls the axis from 0-1

	if(turbo <= 0) //So we ignore inputs from the Right Trigger
	{
		turbo = 0;
	}
	else
	{
		turbo = turbo / 2; //So output will range from 0 to .5, to add to default speed
	}

	if(fabs(forward) < .01)	//To buffer; XStick is sensitive
	{
		forward = 0;
	}

	if(fabs(turn) < .01) //Also to buffer
	{
		turn = 0;
	}

	if(turbo < .01) //Because buffering is in this year
	{
		turbo = 0;
	}

	if(forward < 0)
	{
		turn *= -1;  // Turns the same direction if going forward or backward
	}

	forward *= (.5 + turbo); //So default speed is .5, modified by turbo to a max of 1

	DissectedDrive(forward, turn);


}

void Wheelz::InitWatchdog(bool is)
{
	wheels->SetSafetyEnabled(is);
}

void Wheelz::SetExpiration(float exp)
{
	wheels->SetExpiration(exp);
}

