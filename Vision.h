#include "WPILib.h"

class Vision
{
protected:

	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;


public:

	Vision();
	void StartImageAcquisition();
	void StopImageAcquisition();
	void DrawOval();
	void PutImage();

};
