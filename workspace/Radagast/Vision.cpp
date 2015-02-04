#include "Vision.h"
#include "Defines.h"
#include "WPILib.h"

Vision::Vision()
{
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	//the camera name is cam0, found in roborio web interface
	imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxOpenCamera error: " + std::to_string((long)imaqError) + "\n");
	}
	imaqError = IMAQdxConfigureGrab(session);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxConfigureGrab error: " + std::to_string((long)imaqError) + "\n");
	}


}

void Vision::StartImageAcquisition()
{
	IMAQdxStartAcquisition(session);

}

void Vision::StopImageAcquisition()
{
	IMAQdxStopAcquisition(session);
}

void Vision::DrawOval()
{
	imaqDrawShapeOnImage(frame, frame, { 10, 10, 100, 100 }, DrawMode::IMAQ_DRAW_VALUE, ShapeMode::IMAQ_SHAPE_OVAL, 0.0f);
																								//Draw an oval on it. Because we can.

}

void Vision::GetReports()
{
	/*IMAQdxGrab(session, frame, true, NULL);
	ParticleFilterCriteria2 criteria[] = {
			(IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false)
			//Used to filter out small particles
	};

		//Still need threshold, a la previous years.

		Image *image = frame;

		BinaryImage *convexHullImage = image->ConvexHull(false);  // fill in partial and full rectangles

		BinaryImage *filteredImage = convexHullImage->ParticleFilter(criteria, 1);	//Remove small particles

		delete reports;
		reports = filteredImage->GetOrderedParticleAnalysisReports();  //get a particle analysis report for each particle
		*/
}

void Vision::PutImage()
{
	IMAQdxGrab(session, frame, true, NULL);
	if(imaqError != IMAQdxErrorSuccess) {
		DriverStation::ReportError("IMAQdxGrab error: " + std::to_string((long)imaqError) + "\n");
	} else {
		CameraServer::GetInstance()->SetImage(frame);
		//We call CameraServer::GetInstance() "camera" in Robot.cpp, but it's all the same place
	}
}
