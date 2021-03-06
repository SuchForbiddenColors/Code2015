#include "Wheelz.h"
#include "Defines.h"
#include "Math.h"

Wheelz::Wheelz(int leftMotor, int rightMotor, int aChannel, int bChannel, int cChannel, int dChannel)
{
	wheels = new RobotDrive(leftMotor, rightMotor);
	encoder1 = new Encoder(aChannel, bChannel);
	encoder2 = new Encoder(cChannel, dChannel);

	leftMotorInput = 0;
	rightMotorInput = 0;

}

void Wheelz::DissectedDrive(float forward, float turn)
{
	turn *= TURN_INVERT;

	forward *= FORWARD_INVERT;

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

	leftMotorInput = FORWARD_INVERT * leftSpeed;
	rightMotorInput = FORWARD_INVERT * rightSpeed;
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
		turbo = turbo / X_DRIVE_SPEED_DIVIDER; //So turbo output will range from 0 to .5, to add to default speed
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

	if(fabs(turnInput) < .3)
	{
		turnInput = 0; //Heavy buffer; because any turning precludes forward motion
	}

	if(turnInput == 0)
	{
		forwardInput *= CAREFUL_DRIVE_MAX_FORWARD;
		turn = 0;
		forward = forwardInput;  //So you only move forward/backward
	}
	else //With a nonzero turn input...
	{
		turn = 1;  //We only turn...
		forward = turnInput * CAREFUL_DRIVE_MAX_TURN; //At a speed decided by the turn input
							                         // If turn input is negative, we still give the positive 1 turn value,
						                            //  but the robot will be going "backward", so it will turn the other way
	}

	DissectedDrive(forward, turn);
}

float Wheelz::GetEncoder(int encoderNumber)
{
	float value;

	if(encoderNumber == 1)
	{
		value = encoder1->Get();
	}

	if(encoderNumber == 2)
	{
		value = encoder2->Get();
	}

	return value;
}

float Wheelz::GetDistance(int encoderNumber)
{
	float value;

	if(encoderNumber == 1)
	{
		value = encoder1->Get() * DRIVE_WHEEL_DISTANCE_PER_REVOLUTION / ENCODER_ONE_PULSES_PER_REVOLUTION;
	}

	if(encoderNumber == 1)
	{
		value = encoder2->Get() * DRIVE_WHEEL_DISTANCE_PER_REVOLUTION / ENCODER_TWO_PULSES_PER_REVOLUTION;
	}

	return value;
}

bool Wheelz::GetDirectionEncoder(int encoderNumber)
{
	bool value;
	if(encoderNumber == 1)
	{
		value = encoder1->GetDirection();
	}

	if(encoderNumber == 2)
	{
		value = encoder2->GetDirection();
	}
	return value;
}

void Wheelz::TravelForward(float distance, float speed, int maxRuns) //Auto function, meant to run once per distance
{
	encoder1->Reset(); encoder2->Reset();

	float leftSpeed = speed;
	float rightSpeed = speed;
	int runCount = 0;

	while((fabs(GetDistance(1)) <= distance) && (runCount < maxRuns)) //Assuming distance to always be positive.
	{

		runCount++;
		leftSpeed = speed;
		rightSpeed = speed;
		/*if(GetDistance(1) > GetDistance(2) + GetDistance(2) / 10)
		{
			leftSpeed *= .75;
		}

		if(GetDistance(1) + GetDistance(1) / 10 > GetDistance(2))
		{
			rightSpeed *= .75;
		}

		if(distance - GetDistance(1) < 6)
		{
			leftSpeed *= .5;
			rightSpeed *= .5;
		}*/
		wheels->SetLeftRightMotorOutputs(leftSpeed, rightSpeed);
	}

	wheels->SetLeftRightMotorOutputs(0,0);
}

void Wheelz::TravelAngle(float angle, float speed, bool clockwise, int maxRuns)
{
	encoder1->Reset(); encoder2->Reset();

	float leftSpeed, rightSpeed;

	if(clockwise)
	{
		leftSpeed = speed;
		rightSpeed = -speed;
	}
	else
	{
		leftSpeed = -speed;
		rightSpeed = speed;
	}

	int runCount = 0;

	while((fabs(GetDistance(1))*TURNING_ANGLE_PER_INCH) < angle  && (runCount < maxRuns))
	{
		runCount++;
		wheels->SetLeftRightMotorOutputs(leftSpeed, rightSpeed);
	}

	wheels->SetLeftRightMotorOutputs(0,0);
}

void Wheelz::TurnEncoder(float rotations, float leftSpeed, float rightSpeed)
{											//We want these positive regardless of forward or backward
	float startingRotation;
	float currentRotations = 0;
	startingRotation = encoder1->Get() / ENCODER_ONE_PULSES_PER_REVOLUTION;

	if(rotations > 0)
	{
		while(currentRotations < rotations)
		{
			currentRotations = (encoder1->Get() / ENCODER_ONE_PULSES_PER_REVOLUTION) - startingRotation;

			wheels->SetLeftRightMotorOutputs(leftSpeed, rightSpeed);

		}
		wheels->SetLeftRightMotorOutputs(0, 0);
	}

	if(rotations < 0)
	{
		while(currentRotations > rotations)
		{
			currentRotations = (encoder1->Get() / ENCODER_ONE_PULSES_PER_REVOLUTION) - startingRotation;

			wheels->SetLeftRightMotorOutputs(-leftSpeed, -rightSpeed);

		}
		wheels->SetLeftRightMotorOutputs(0, 0);
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


