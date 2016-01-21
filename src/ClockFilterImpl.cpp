#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "ClockFilterImpl.hpp"

using namespace cv;
using namespace std;

Point clockCenterPosition;
Point clockTopPosition;
Point bigHandPosition;
Point smallHandPosition;
int auswahlRadius;

ClockFilterImpl::~ClockFilterImpl()
{
}

int isPointInCircle(Point point){
	int squareDistance = (clockCenterPosition.x - point.x)*(clockCenterPosition.x - point.x) + (clockCenterPosition.y - point.y)*(clockCenterPosition.y - point.y);
	if (squareDistance < auswahlRadius);
	{
		return true;
	}
}

static double angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}


void ClockFilterImpl::process(const cv::Mat& input)
{

	Mat cameraFrame = input;
	vector<Mat> rgb;
	Mat cameraFrameCircle = input;
	Mat cameraGray;
	Mat cameraThreshold;
	Mat cameraGrayBlurred;
	Mat canny;

	//farbkonvertierung nach grau
	cvtColor(cameraFrame, cameraGray, CV_BGR2GRAY);
	//split in rgb
	split(cameraFrame, rgb);
	//blurfilter für die kreiserkennung
	GaussianBlur(cameraGray, cameraGrayBlurred, Size(9, 9), 2, 2);
	//arrays für die kreise
	vector<Vec3f> circles;
	//erkennen der kreise mittels houghcircle
	HoughCircles(cameraGrayBlurred, circles, CV_HOUGH_GRADIENT, 1, cameraGrayBlurred.rows / 8, 200, 100, cameraGrayBlurred.rows / 4, cameraGrayBlurred.cols * 2);
	//einzeichnen der kreise
	if (!circles.empty()){
		for (size_t i = 0; i < circles.size(); i++){
			//kreis zentrum 
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// kreis zentrum ausgeben und einzeichnen 
			//cout << center;
			circle(cameraFrameCircle, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			// kreis einzeichnen
			circle(cameraFrameCircle, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			//aktualisieren des uhrmittelpunkts
			clockCenterPosition = center;
			auswahlRadius = radius;
		}
	}

	//helligkeit des blauen bildanteils weiterbearbeiten für die findContours funktion
	Canny(rgb[0], canny, 150, 200, 3);
	dilate(canny, canny, Mat(), Point(-1, -1));

	//find contours
	vector<vector<Point>> contours;

	findContours(canny, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// The array for storing the approximation curve
	vector<Point> approx;

	Point centerOfTriangle(0, 0);
	Point centerOfBigHand(0, 0);
	Point centerOfSmallHand(0, 0);

	int largestArea = 0;
	for (size_t i = 0; i < contours.size(); i++) {
		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
		if (//genau drei ecken
			approx.size() == 3
			//fläche des dreiecks
			&& fabs(contourArea(Mat(approx))) > 1.8*auswahlRadius    //300
			&& fabs(contourArea(Mat(approx))) < 2.5*auswahlRadius	   //1500	
			//ist das dreieck geschlossen
			&& isContourConvex(Mat(approx))
			) {
			for (size_t i = 0; i < approx.size(); i++){
				centerOfTriangle.x += approx[i].x;
				centerOfTriangle.y += approx[i].y;
			}
			centerOfTriangle.x /= 3;
			centerOfTriangle.y /= 3;
			if (isPointInCircle(centerOfTriangle)){

				cout << "centeroftriangle: ";
				cout << centerOfTriangle << endl;
				cout << "triangleArea " << contourArea(Mat(approx)) << endl;
				cout << "auswahlradius" << auswahlRadius << endl;
				cout << endl;
				clockTopPosition = centerOfTriangle;
			}
		
		}else if (//genau vier ecken für bighand
			approx.size() == 4
			//fläche des vierecks
			&& fabs(contourArea(Mat(approx))) >	10 * auswahlRadius // 400
			&& fabs(contourArea(Mat(approx))) < 15 * auswahlRadius
			//ist das viereck geschlossen
			&& isContourConvex(Mat(approx))
			) {
			double maxCosine = 0;
			for (int j = 2; j < 5; j++){
				// find the maximum cosine of the angle between joint edges
				double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
				maxCosine = MAX(maxCosine, cosine);
			}
			if (maxCosine < 0.3){
				for (size_t i = 0; i < approx.size(); i++){
					centerOfBigHand.x += approx[i].x;
					centerOfBigHand.y += approx[i].y;
				}
				centerOfBigHand.x /= 4;
				centerOfBigHand.y /= 4;
				if (isPointInCircle(centerOfBigHand)){
					cout << "centerOfBigHand: ";
					cout << centerOfBigHand << endl;
					cout << "quadarea " << contourArea(Mat(approx)) << endl;
					cout << "auswahlradius: " << auswahlRadius << endl;
					cout << endl;
					bigHandPosition = centerOfBigHand;
				}
			}
		}
		else if ( //genau vier ecken für smallhand
			approx.size() == 4
			//fläche des vierecks
			&& fabs(contourArea(Mat(approx))) > 5 * auswahlRadius // 400
			&& fabs(contourArea(Mat(approx))) < 9 * auswahlRadius
			//ist das viereck geschlossen
			&& isContourConvex(Mat(approx))
			) {
			double maxCosine = 0;
			for (int j = 2; j < 5; j++){
				//berechnen des maximalen cosinus in den ecken
				double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
				maxCosine = MAX(maxCosine, cosine);
			}
			if (maxCosine < 0.3){
				for (size_t i = 0; i < approx.size(); i++){
					centerOfSmallHand.x += approx[i].x;
					centerOfSmallHand.y += approx[i].y;
				}
				centerOfSmallHand.x /= 4;
				centerOfSmallHand.y /= 4;
				if (isPointInCircle(centerOfSmallHand)){
					cout << "centerOfSmallHand: ";
					cout << centerOfSmallHand << endl;
					cout << "quadarea " << contourArea(Mat(approx)) << endl;
					cout << "auswahlradius: " << auswahlRadius << endl;
					cout << endl;
					smallHandPosition = centerOfSmallHand;
				}
			}
		}
	}	
	
	//Einzeichnen der Debugging punkte auf den zeigern

	circle(cameraFrameCircle, centerOfTriangle, 3, Scalar(0, 255, 0), -1, 8, 0);
	circle(cameraFrameCircle, centerOfSmallHand, 3, Scalar(0, 255, 255), -1, 8, 0);
	circle(cameraFrameCircle, centerOfBigHand, 3, Scalar(0, 0, 255), -1, 8, 0);


	//debugging bildausgaben
	imshow("canny", canny);
	//	imshow("red", rgb[2]);
	//	imshow("green",rgb[1]);
	//	imshow("blue",rgb[0]);

	//cv::imshow("Debug", cameraFrameCircle);


}

cv::Point ClockFilterImpl::getBigHandPosition() const
{
	return bigHandPosition;
}

cv::Point ClockFilterImpl::getSmallHandPosition() const
{
	return smallHandPosition;
}

cv::Point ClockFilterImpl::getClockCenterPosition() const
{
	return clockCenterPosition;
}

cv::Point ClockFilterImpl::getClockTopPosition() const
{
	return clockTopPosition;
}