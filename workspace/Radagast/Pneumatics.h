#include "WPILib.h"

class Pneumatics {

protected:
	Compressor *compress;
	Solenoid *sol1, *sol2, *sol3, *sol4, *sol5, *sol6, *sol7, *sol8;

	bool solOneOn;
	bool solTwoOn;
	bool solThreeOn;
	bool solFourOn;
	bool solFiveOn;
	bool solSixOn;
	bool solSevenOn;
	bool solEightOn;

public:
	Pneumatics();
	void SolenoidFlip(int solNum);


};
