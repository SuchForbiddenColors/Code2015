#include "Pneumatics.h"
#include "Defines.h"

Pneumatics::Pneumatics()
{
	compress = new Compressor();
	compress->Start();

	sol1 = new Solenoid(0);
	sol2 = new Solenoid(1);
	sol3 = new Solenoid(2);
	sol4 = new Solenoid(3);
	sol5 = new Solenoid(4);
	sol6 = new Solenoid(5);
	sol7 = new Solenoid(6);
	sol8 = new Solenoid(7);

	sol1->Set(false); //Extend piston
	solOneOn = false;

	sol2->Set(true); //Retract piston
	solTwoOn = true;

	sol3->Set(true);
	solThreeOn = true;

	sol4->Set(true);
	solFourOn = true;

	sol5->Set(true);
	solFiveOn = true;

	sol6->Set(true);
	solSixOn = true;

	sol7->Set(true);
	solSevenOn = true;

	sol8->Set(true);
	solEightOn = true;


}

void Pneumatics::SolenoidFlip(int solNum)
{
	if(solNum == 1)
		{
			if(solOneOn == true)
			{
				sol1->Set(false);
				solOneOn = false;
			}
			else if(solOneOn == false)
			{
				sol1->Set(true);
				solOneOn = true;
			}
		}

	if(solNum == 2)
		{
			if(solTwoOn == true)
			{
				sol2->Set(false);
				solTwoOn = false;

			}
			else if(solTwoOn == false)
			{
				sol2->Set(true);
				solTwoOn = true;
			}
		}

	if(solNum == 3)
			{
				if(solThreeOn == true)
				{
					sol3->Set(false);
					solThreeOn = false;

				}
				else if(solThreeOn == false)
				{
					sol3->Set(true);
					solThreeOn = true;
				}
			}

	if(solNum == 4)
			{
				if(solFourOn == true)
				{
					sol4->Set(false);
					solFourOn = false;

				}
				else if(solFourOn == false)
				{
					sol4->Set(true);
					solFourOn = true;
				}
			}

	if(solNum == 5)
		{
			if(solFiveOn == true)
			{
				sol5->Set(false);
				solFiveOn = false;
			}
			else if(solFiveOn == false)
			{
				sol5->Set(true);
				solFiveOn = true;
			}
		}

	if(solNum == 6)
		{
			if(solSixOn == true)
			{
				sol6->Set(false);
				solSixOn = false;

			}
			else if(solSixOn == false)
			{
				sol6->Set(true);
				solSixOn = true;
			}
		}

	if(solNum == 7)
			{
				if(solSevenOn == true)
				{
					sol7->Set(false);
					solSevenOn = false;

				}
				else if(solSevenOn == false)
				{
					sol7->Set(true);
					solSevenOn = true;
				}
			}

	if(solNum == 8)
			{
				if(solEightOn == true)
				{
					sol8->Set(false);
					solEightOn = false;

				}
				else if(solEightOn == false)
				{
					sol8->Set(true);
					solEightOn = true;
				}
			}
}
