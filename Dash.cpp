#include "Dash.h"
#include <string>

using namespace std;


Dash::Dash(Wheelz *wheels, Pneumatics *air)
{
	whe = wheels;
	pne = air;
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
