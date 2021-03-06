#include "Dash.h"
#include <string>


using namespace std;


Dash::Dash(Wheelz *wheels, Pneumatics *air, BuiltInAccelerometer *excel, Joystick *XStick, Joystick * TwoStick, Elevator *rise)
{
	whe = wheels;
	pne = air;
	ace = excel;
	one = XStick;
	twe = TwoStick;
	ele = rise;

	x_HasBeenPressed = false;
	y_HasBeenPressed = false;
	a_HasBeenPressed = false;
	b_HasBeenPressed = false;
	start_HasBeenPressed = false;
	rightBumper_HasBeenPressed = false;
	z_HasBeenPressed = false;
	m_HasBeenPressed = false;

	leftEnergy = 0;
	rightEnergy = 0;
	distance1 = 0;
	distance2 = 0;
	currentHeight = 20;
}

void Dash::PutString(int lineNum, string message)
{									// Copypaste alley
	if(lineNum == 1)  //TODO: Build the string manually using the lineNum - 1 input
		{
			SmartDashboard::PutString("DB/String 0", message);
		}

	if(lineNum == 2)
		{
			SmartDashboard::PutString("DB/String 1", message);
		}

	if(lineNum == 3)
		{
			SmartDashboard::PutString("DB/String 2", message);
		}

	if(lineNum == 4)
		{
			SmartDashboard::PutString("DB/String 3", message);
		}

	if(lineNum == 5)
		{
			SmartDashboard::PutString("DB/String 4", message);
		}

	if(lineNum == 6)
		{
			SmartDashboard::PutString("DB/String 5", message);
		}

	if(lineNum == 7)
		{
			SmartDashboard::PutString("DB/String 6", message);
		}

	if(lineNum == 8)
		{
			SmartDashboard::PutString("DB/String 7", message);
		}

	if(lineNum == 9)
		{
			SmartDashboard::PutString("DB/String 8", message);
		}

	if(lineNum == 10)
		{
			SmartDashboard::PutString("DB/String 9", message);
		}
}

void Dash::PutNumber(int sliderNum, float number)
{
	if(sliderNum == 1)
		{
			SmartDashboard::PutNumber("DB/Slider 0", number);
		}
	if(sliderNum == 2)
		{
			SmartDashboard::PutNumber("DB/Slider 1", number);
		}
	if(sliderNum == 3)
		{
			SmartDashboard::PutNumber("DB/Slider 2", number);
		}
	if(sliderNum == 4)
		{
			SmartDashboard::PutNumber("DB/Slider 3", number);
		}
}

void Dash::PutBool(int buttonNum, bool value)
{
	if(buttonNum == 1)
	{
		SmartDashboard::PutBoolean("DB/Button 0", value);
	}
	if(buttonNum == 2)
	{
		SmartDashboard::PutBoolean("DB/Button 1", value);
	}
	if(buttonNum == 3)
	{
		SmartDashboard::PutBoolean("DB/Button 2", value);
	}
	if(buttonNum == 4)
	{
		SmartDashboard::PutBoolean("DB/Button 3", value);
	}

}

string Dash::GetString(int lineNum)
{
	string word;

	if(lineNum == 1)
		{
			word = SmartDashboard::GetString("DB/String 0", "Fail");
		}

	if(lineNum == 2)
		{
			word = SmartDashboard::GetString("DB/String 1", "Fail");
		}

	if(lineNum == 3)
		{
			word = SmartDashboard::GetString("DB/String 2", "Fail");
		}

	if(lineNum == 4)
		{
			word = SmartDashboard::GetString("DB/String 3", "Fail");
		}

	if(lineNum == 5)
		{
			word = SmartDashboard::GetString("DB/String 4", "Fail");
		}

	if(lineNum == 6)
		{
			word = SmartDashboard::GetString("DB/String 5", "Fail");
		}

	if(lineNum == 7)
		{
			word = SmartDashboard::GetString("DB/String 6", "Fail");
		}

	if(lineNum == 8)
		{
			word = SmartDashboard::GetString("DB/String 7", "Fail");
		}

	if(lineNum == 9)
		{
			word = SmartDashboard::GetString("DB/String 8", "Fail");
		}

	if(lineNum == 10)
		{
			word = SmartDashboard::GetString("DB/String 9", "Fail");
		}

	cout << word;
	return word;
}

float Dash::GetNumber(int sliderNum)
{
	float value;

	if(sliderNum == 1)
		{
			value = SmartDashboard::GetNumber("DB/Slider 0");
		}
	if(sliderNum == 2)
		{
			value = SmartDashboard::GetNumber("DB/Slider 1");
		}
	if(sliderNum == 3)
		{
			value = SmartDashboard::GetNumber("DB/Slider 2");
		}
	if(sliderNum == 4)
		{
			value = SmartDashboard::GetNumber("DB/Slider 3");
		}

	return value;
}

void Dash::AddEnergyToTotal(double time)
{
	leftEnergy += time * whe->leftMotorInput;
				//The energy we told left motor to be at, times the time, in seconds,
			   // we told it to be at that energy for.

	rightEnergy += time * whe->rightMotorInput;
}

void Dash::SetEncoderDistance()
{
	distance1 = whe->GetEncoder(1) / ENCODER_ONE_PULSES_PER_REVOLUTION * DRIVE_WHEEL_DISTANCE_PER_REVOLUTION;
										//Turns pulses into distance in feet
	distance2 = whe->GetEncoder(2) / ENCODER_ONE_PULSES_PER_REVOLUTION * DRIVE_WHEEL_DISTANCE_PER_REVOLUTION;
}

void Dash::EncoderCount(int sliderNum, int encoderNumber)
{
	float rotationCount = whe->GetEncoder(encoderNumber) / ENCODER_ONE_PULSES_PER_REVOLUTION;
	rotationCount *= 100; //Make it a percentage

	PutNumber(sliderNum, rotationCount);
}

void Dash::Acceleration(int sliderNum, int axis)
{
	if(axis == 1)
	{
		PutNumber(sliderNum, ace->GetX());
	}
	else if(axis == 2)
	{
		PutNumber(sliderNum, ace->GetY());
	}
	else if(axis == 3)
	{
		PutNumber(sliderNum, ace->GetZ());
	}
}

void Dash::LimitSwitch(int buttonNum, int limitSwitch)
{
	if(limitSwitch == 1)
	{
		PutBool(buttonNum, ele->upperLimit->Get());
	}

	if(limitSwitch == 2)
	{
		PutBool(buttonNum, ele->lowerLimit->Get());
	}
}

void Dash::Pistons(int lineNumber)
{
	string message;

	string partOne, partTwo;


		if(pne->solOneOn && (pne->solTwoOn == false)) // 1 and 3 retract
		{
			partOne = "L Closed,";
		}
		else
		{
			partOne = "L Open, ";
		}

		if(pne->solThreeOn && (pne->solFourOn == false))
		{
			partTwo = "R Closed";
		}
		else
		{
			partTwo = "R Open";
		}


	message = partOne + partTwo;

	PutString(lineNumber, message);
}

void Dash::LiftHeight(int sliderNum)
{
	currentHeight = 57 - ele->stringPot->Get(); //57 This is for realbot; 54.95 on practice bot
		//TODO: Adjust for realbot

	if(sliderNum == 1 || sliderNum == 2 || sliderNum == 3 || sliderNum == 4)
	{
		PutNumber(sliderNum, currentHeight);
	}
}

void Dash::DistancePerEnergy(int sliderNum)
{
	float ratio;
	if(leftEnergy == 0)
	{
		ratio = 0;
	}

	ratio = distance1 / (leftEnergy * 40); //Want changes in distance and in energy to be noticeable
										 // It's an art, not a science.
	PutNumber(sliderNum, ratio);
}

bool Dash::StickyPress(char button)
{
	if(button == 'x')
	{
		if(one->GetRawButton(X_X) && x_HasBeenPressed == false)
		{
			x_HasBeenPressed = true;
			return true;
		}

		//We only get to this half of the function if it does not return true
		//So therefore we want it to return false

		if(one->GetRawButton(X_X) == false)
		{
			x_HasBeenPressed = false;
		}

		return false;
	}

	if(button == 'y')
	{
		if(one->GetRawButton(X_Y) && y_HasBeenPressed == false)
		{
			y_HasBeenPressed = true;
			return true;
		}

		if(one->GetRawButton(X_Y) == false)
		{
			y_HasBeenPressed = false;
		}

		return false;
	}

	if(button == 'a')
	{
		if(one->GetRawButton(X_A) && a_HasBeenPressed == false)
		{
			a_HasBeenPressed = true;
			return true;
		}

		if(one->GetRawButton(X_A) == false)
		{
			a_HasBeenPressed = false;
		}

		return false;
	}

	if(button == 'b')
	{
		if(one->GetRawButton(X_B) && b_HasBeenPressed == false)
		{
			b_HasBeenPressed = true;
			return true;
		}

		if(one->GetRawButton(X_B) == false)
		{
			b_HasBeenPressed = false;
		}

		return false;
	}

	if(button == 's') //s is for start
	{
		if(one->GetRawButton(X_START) && start_HasBeenPressed == false)
		{
			start_HasBeenPressed = true;
			return true;
		}

		if(one->GetRawButton(X_START) == false)
		{
			start_HasBeenPressed = false;
		}

			return false;
	}

	if(button == 'r') //r is for right bumper
	{
		if(one->GetRawButton(X_RIGHT_BUMPER) && rightBumper_HasBeenPressed == false)
		{
			rightBumper_HasBeenPressed = true;
			return true;
		}

		if(one->GetRawButton(X_RIGHT_BUMPER) == false)
		{
			rightBumper_HasBeenPressed = false;
		}
	}

	if(button == 'z')//TwoStick's leftBumper
	{
		if(twe->GetRawButton(X_LEFT_BUMPER) && z_HasBeenPressed == false)
		{
			z_HasBeenPressed = true;
			return true;
		}

		if(twe->GetRawButton(X_LEFT_BUMPER) == false)
		{
			z_HasBeenPressed = false;
		}
	}

	if(button == 'm')//TwoStick's rightBumper
		{
			if(twe->GetRawButton(X_RIGHT_BUMPER) && m_HasBeenPressed == false)
			{
				m_HasBeenPressed = true;
				return true;
			}

			if(twe->GetRawButton(X_RIGHT_BUMPER) == false)
			{
				m_HasBeenPressed = false;
			}
		}

		return false; //If we get all the way through with no buttons selected
}													//Just return false
