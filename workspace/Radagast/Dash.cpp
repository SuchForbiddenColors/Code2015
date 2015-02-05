#include "Dash.h"
#include <string>

using namespace std;


Dash::Dash(Wheelz *wheels, Pneumatics *air, BuiltInAccelerometer *excel, Joystick *XStick)
{
	whe = wheels;
	pne = air;
	ace = excel;
	one = XStick;

	x_HasBeenPressed = false;
	y_HasBeenPressed = false;
	a_HasBeenPressed = false;
	b_HasBeenPressed = false;

	leftEnergy = 0;
	rightEnergy = 0;
	distance = 0;
}

void Dash::PutString(int lineNum, string message)
{									// Copypaste alley
	if(lineNum == 1)
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

string Dash::GetString(int lineNum)
{
	string word;

	if(lineNum == 1)
		{
			word = SmartDashboard::GetString("DB/String 0");
		}

	if(lineNum == 2)
		{
			word = SmartDashboard::GetString("DB/String 1");
		}

	if(lineNum == 3)
		{
			word = SmartDashboard::GetString("DB/String 2");
		}

	if(lineNum == 4)
		{
			word = SmartDashboard::GetString("DB/String 3");
		}

	if(lineNum == 5)
		{
			word = SmartDashboard::GetString("DB/String 4");
		}

	if(lineNum == 6)
		{
			word = SmartDashboard::GetString("DB/String 5");
		}

	if(lineNum == 7)
		{
			word = SmartDashboard::GetString("DB/String 6");
		}

	if(lineNum == 8)
		{
			word = SmartDashboard::GetString("DB/String 7");
		}

	if(lineNum == 9)
		{
			word = SmartDashboard::GetString("DB/String 8");
		}

	if(lineNum == 10)
		{
			word = SmartDashboard::GetString("DB/String 9");
		}

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

void Dash::SetDistance()
{
	distance = whe->GetEncoder() / ENCODER_ONE_PULSES_PER_REVOLUTION * DRIVE_WHEEL_DISTANCE_PER_REVOLUTION;
										//Turns pulses into distance in feet
}

void Dash::EncoderCount(int sliderNum)
{
	float rotationCount = whe->GetEncoder() / ENCODER_ONE_PULSES_PER_REVOLUTION;
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

void Dash::DistancePerEnergy(int sliderNum)
{
	float ratio;
	if(leftEnergy == 0)
	{
		ratio = 0;
	}

	ratio = distance / leftEnergy;

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
	else
	{
		return false;
	}

}

