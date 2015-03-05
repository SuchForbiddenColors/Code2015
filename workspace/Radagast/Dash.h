#include "WPILib.h"
#include "Wheelz.h"
#include "Pneumatics.h"
#include "Vision.h"
#include "Elevator.h"
#include "Defines.h"


using namespace std;

class Dash {
protected:
	Wheelz *whe;
	Pneumatics *pne;
	BuiltInAccelerometer *ace;
	Joystick *one;
	Elevator *ele;

	bool x_HasBeenPressed;
	bool y_HasBeenPressed;
	bool a_HasBeenPressed;
	bool b_HasBeenPressed;
	bool start_HasBeenPressed;
	bool rightBumper_HasBeenPressed;

	float leftEnergy;
	float rightEnergy;
	float distance1; //TODO: Get leftDistance and rightDistance after we have wheel-specific encoders
	float distance2;

public:
	float currentHeight;

	Dash(Wheelz *wheels, Pneumatics *air, BuiltInAccelerometer *excel, Joystick *XStick, Elevator *rise);
	void PutString(int lineNum, string message);
	void PutNumber(int sliderNum, float number);
	void PutBool(int buttonNum, bool value);

	string GetString(int lineNum); //Returns the string at a line of the dashboard
	float GetNumber(int sliderNum); //Returns the number at a slider of the dashboard

	void AddEnergyToTotal(double time);
	void SetEncoderDistance();

	void EncoderCount(int sliderNum, int encoderNumber); //Writes the percentage of encoder rotations on a slider on the dashboard
	void Acceleration(int sliderNum, int axis);
	void LimitSwitch(int buttonNum, int limitSwitch); //Returns value of chosen switch
	void SolenoidPair(int lineNum, int solenoidPair);
	void LiftHeight(int sliderNum); //Returns in inches //Run every loop so we have currentHeight, give invalid sliderNum to not print it
	void DistancePerEnergy(int sliderNum);

	bool StickyPress(char button); //Will work best if run every loop
};
