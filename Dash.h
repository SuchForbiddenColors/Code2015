#include "WPILib.h"
#include "Wheelz.h"
#include "Pneumatics.h"


using namespace std;

class Dash {
protected:
	Wheelz *whe;
	Pneumatics *pne;



public:
	Dash(Wheelz *wheels, Pneumatics *air);
	void PutString(int lineNum, string message);




};
