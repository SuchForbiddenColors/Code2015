#include "Wheelz.h"
#include "Defines.h"
#include "Math.h"

Wheelz::Wheelz(int leftMotor, int rightMotor, int aChannel, int bChannel)
{
	wheels = new RobotDrive(leftMotor, rightMotor);
	encoder = new Encoder(aChannel, bChannel);

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
			leftSpeed = forward / ratio;							 //  It's here in case we need to modify it
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
	float forward = XStick->GetRawAxis(1); //1 is a controller's LeftY
	float turn = XStick->GetRawAxis(4); //4 is a controller's RightX
	float turbo = XStick->GetRawAxis(2); //2 seems to be left trigger now

	if(turbo <= 0) //So we ignore inputs from the Right Trigger //Probably arcaizante
	{
		turbo = 0;
	}
	else
	{
		turbo = turbo / 2; //So turbo output will range from 0 to .5, to add to default speed
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

	turn *= TURN_INVERT;

	DissectedDrive(forward, turn);


}

void Wheelz::CarefulDrive(GenericHID * XStick)
{
	float forwardInput = XStick->GetRawAxis(1); //LeftY
	float turnInput = XStick->GetRawAxis(4);//RightX
	float turn;
	float forward;

	if(fabs(forwardInput) < .01)
	{
		forwardInput = 0; //Light buffer
	}

	if(fabs(turnInput) < .075)
	{
		turnInput = 0; //Heavy buffer; because any turning precludes forward motion
	}

	if(turnInput == 0)
	{
		forwardInput *= .4;  //Max of 40% speed
		turn = 0;
		forward = forwardInput;  //So you only move forward/backward
	}
	else //With a nonzero turn input...
	{
		turn = 1;  //We only turn...
		forward = turnInput; //At a speed decided by the turn input
	}
}

float Wheelz::GetEncoder()
{
	float value = encoder->Get();
	return value;
}

bool Wheelz::GetDirectionEncoder()
{
	bool value = encoder->GetDirection();
	return value;
}

void Wheelz::EncoderTurn(float rotations, Victor *testMotor)
{
	float startingRotation;
	float currentRotations = 0;
	startingRotation = encoder->Get() / ENCODER_ONE_PULSES_PER_REVOLUTION;

	if(rotations > 0)
	{
		while(currentRotations < rotations)
		{
			currentRotations = (encoder->Get() / ENCODER_ONE_PULSES_PER_REVOLUTION) - startingRotation;

			testMotor->Set(.5);

		}
		testMotor->Set(0);
	}

	if(rotations < 0)
	{
		while(currentRotations > rotations)
		{
			currentRotations = (encoder->Get() / ENCODER_ONE_PULSES_PER_REVOLUTION) - startingRotation;

			testMotor->Set(-.5);

		}
		testMotor->Set(0);
	}
}

void Wheelz::InitWatchdog(bool is)
{
	wheels->SetSafetyEnabled(is);
}

void Wheelz::SetExpiration(float exp)
{
	wheels->SetExpiration(exp);
}


