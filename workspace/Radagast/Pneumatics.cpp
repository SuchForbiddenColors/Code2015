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

	sol1->Set(false); //Extend piston
	solOneOn = false;

	sol2->Set(true); //Retract piston
	solTwoOn = true;

	sol3->Set(true);
	solThreeOn = true;

	sol4->Set(true);
	solFourOn = true;


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
}
