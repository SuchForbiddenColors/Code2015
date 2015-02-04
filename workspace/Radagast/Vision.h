#include "WPILib.h"

using namespace std;

class Vision
{
protected:

	IMAQdxSession session;
	Image *frame;
	IMAQdxError imaqError;

	ParticleAnalysisReport bestParticleReport;
	vector <ParticleAnalysisReport> *reports;


public:

	Vision();
	void StartImageAcquisition();
	void StopImageAcquisition();
	void DrawOval();
	void GetReports();
	void PutImage();

	struct Scores {
		double rectangularity;
		double aspectRatioVertical;
		double aspectRatioHorizontal;
	};

};
