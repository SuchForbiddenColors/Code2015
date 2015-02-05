#include "WPILib.h"
#include "Wheelz.h"
#include "Pneumatics.h"
#include "Vision.h"
#include "Defines.h"


using namespace std;

class Dash {
protected:
	Wheelz *whe;
	Pneumatics *pne;
	BuiltInAccelerometer *ace;
	Joystick *one;

	bool x_HasBeenPressed;
	bool y_HasBeenPressed;
	bool a_HasBeenPressed;
	bool b_HasBeenPressed;

	float leftEnergy;
	float rightEnergy;
	float distance; //TODO: Get leftDistance and rightDistance after we have wheel-specific encoders

public:
	Dash(Wheelz *wheels, Pneumatics *air, BuiltInAccelerometer *excel, Joystick *XStick);
	void PutString(int lineNum, string message);
	void PutNumber(int sliderNum, float number);

	string GetString(int lineNum); //Returns the string at a line of the dashboard
	float GetNumber(int sliderNum); //Returns the number at a slider of the dashboard

	void AddEnergyToTotal(double time);
	void SetDistance();

	void EncoderCount(int sliderNum); //Writes the percentage of encoder rotations on a slider on the dashboard
	void Acceleration(int sliderNum, int axis);
	void DistancePerEnergy(int sliderNum);

	bool StickyPress(char button); //Will work best if run every loop
};
