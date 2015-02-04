#include "WPILib.h"

class Pneumatics {

protected:
	Compressor *compress;
	Solenoid *sol1, *sol2, *sol3, *sol4;

	bool solOneOn;
	bool solTwoOn;
	bool solThreeOn;
	bool solFourOn;

public:
	Pneumatics();
	void SolenoidFlip(int solNum);


};
