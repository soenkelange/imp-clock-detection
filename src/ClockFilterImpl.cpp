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
	Mat cameraLines;
	Mat canny;
	Mat canny1;
	Mat cannyGray;
	Mat circleInside;

	//farbkonvertierung nach grau
	cvtColor(cameraFrame, cameraGray, CV_BGR2GRAY);
	//split in rgb
	split(cameraFrame, rgb);
	//blurfilter für die kreiserkennung
	GaussianBlur(cameraGray, cameraGrayBlurred, Size(9, 9), 2, 2);
	//arrays für die kreise
	vector<Vec3f> circles;

	//erkennen der kreise mittels houghcircle
	//evtl nicht blurred
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

	//get lines		
	Canny(rgb[0], canny, 150, 200, 3);
	//blur(rgb[0], rgb[0], Size(3, 3));

	Canny(rgb[0], canny1, 150, 200, 3);

	dilate(canny, canny, Mat(), Point(-1, -1));
	dilate(canny1, canny1, Mat(), Point(-1, -1));

	//find contours
	vector<vector<Point>> triContours;
	vector<vector<Point>> quadContours;

	findContours(canny, triContours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	findContours(canny1, quadContours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// The array for storing the approximation curve
	vector<Point> triApprox;
	vector<Point> quadApprox;


	Point centerOfTriangle(0, 0);
	Point centerOfBigHand(0, 0);
	Point centerOfSmallHand(0, 0);

	int largestArea = 0;
	for (size_t i = 0; i < triContours.size(); i++) {
		approxPolyDP(Mat(triContours[i]), triApprox, arcLength(Mat(triContours[i]), true)*0.02, true);
		if (//genau drei ecken
			triApprox.size() == 3
			//fläche des dreiecks
			&& fabs(contourArea(Mat(triApprox))) > 0.2*auswahlRadius    //300
			&& fabs(contourArea(Mat(triApprox))) < 3.5*auswahlRadius	   //1500	
			//ist das dreieck geschlossen
			&& isContourConvex(Mat(triApprox))
			) {
			for (size_t i = 0; i < triApprox.size(); i++){
				centerOfTriangle.x += triApprox[i].x;
				centerOfTriangle.y += triApprox[i].y;
			}
			centerOfTriangle.x /= 3;
			centerOfTriangle.y /= 3;
			if (isPointInCircle(centerOfTriangle)){

				cout << "centeroftriangle: ";
				cout << centerOfTriangle << endl;
				cout << "triangleArea " << contourArea(Mat(triApprox)) << endl;
				cout << "auswahlradius" << auswahlRadius << endl;
				cout << endl;


				clockTopPosition = centerOfTriangle;
			}
		}
	}
	circle(cameraFrameCircle, centerOfTriangle, 3, Scalar(0, 255, 0), -1, 8, 0);

	for (size_t i = 0; i < quadContours.size(); i++) {
		approxPolyDP(Mat(quadContours[i]), quadApprox, arcLength(Mat(quadContours[i]), true)*0.02, true);

		if (//genau vier ecken
			quadApprox.size() == 4
			//fläche des vierecks
			&& fabs(contourArea(Mat(quadApprox))) >	10 * auswahlRadius // 400
			&& fabs(contourArea(Mat(quadApprox))) < 15 * auswahlRadius
			//ist das viereck geschlossen
			&& isContourConvex(Mat(quadApprox))
			) {
			double maxCosine = 0;

			for (int j = 2; j < 5; j++)
			{
				// find the maximum cosine of the angle between joint edges
				double cosine = fabs(angle(quadApprox[j % 4], quadApprox[j - 2], quadApprox[j - 1]));
				maxCosine = MAX(maxCosine, cosine);
			}

			// if cosines of all angles are small
			// (all angles are ~90 degree) then write quandrange
			// vertices to resultant sequence
			if (maxCosine < 0.3){
				for (size_t i = 0; i < quadApprox.size(); i++){
					centerOfBigHand.x += quadApprox[i].x;
					centerOfBigHand.y += quadApprox[i].y;
				}
				centerOfBigHand.x /= 4;
				centerOfBigHand.y /= 4;
				if (isPointInCircle(centerOfBigHand)){
					cout << "centerOfBigHand: ";
					cout << centerOfBigHand << endl;
					cout << "quadarea " << contourArea(Mat(quadApprox)) << endl;
					cout << "auswahlradius: " << auswahlRadius << endl;
					cout << endl;


					bigHandPosition = centerOfBigHand;
				}
			}

		}
		else if (
			//genau vier ecken
			quadApprox.size() == 4
			//fläche des vierecks
			&& fabs(contourArea(Mat(quadApprox))) > 3 * auswahlRadius // 400
			&& fabs(contourArea(Mat(quadApprox))) < 9 * auswahlRadius
			//ist das viereck geschlossen
			&& isContourConvex(Mat(quadApprox))
			) {
			double maxCosine = 0;

			for (int j = 2; j < 5; j++)
			{
				// find the maximum cosine of the angle between joint edges
				double cosine = fabs(angle(quadApprox[j % 4], quadApprox[j - 2], quadApprox[j - 1]));
				maxCosine = MAX(maxCosine, cosine);
			}

			// if cosines of all angles are small
			// (all angles are ~90 degree) then write quandrange
			// vertices to resultant sequence
			if (maxCosine < 0.3){

				for (size_t i = 0; i < quadApprox.size(); i++){
					centerOfSmallHand.x += quadApprox[i].x;
					centerOfSmallHand.y += quadApprox[i].y;
				}
				centerOfSmallHand.x /= 4;
				centerOfSmallHand.y /= 4;
				if (isPointInCircle(centerOfSmallHand)){


					cout << "centerOfSmallHand: ";
					cout << centerOfSmallHand << endl;
					cout << "quadarea " << contourArea(Mat(quadApprox)) << endl;
					cout << "auswahlradius: " << auswahlRadius << endl;
					cout << endl;


					smallHandPosition = centerOfSmallHand;
				}
			}
		}
	}

	//Einzeichnen der Debugging punkte auf den zeigern
	circle(cameraFrameCircle, centerOfSmallHand, 3, Scalar(0, 255, 255), -1, 8, 0);

	circle(cameraFrameCircle, centerOfBigHand, 3, Scalar(0, 0, 255), -1, 8, 0);


	//debugging bildausgaben

	//	imshow("cam", cameraFrame);
	//	imshow("camGray", cameraGray);
	imshow("cameraFrameCircle", cameraFrameCircle);
	//	imshow("camLines", cameraLines);
	//	imshow("circle inside", circleInside);
	imshow("canny", canny);
	//	imshow("red", rgb[2]);
	//	imshow("green",rgb[1]);
	//	imshow("blue",rgb[0]);
	imshow("canny rbg 0", canny1);



	cv::imshow("Debug", cameraFrameCircle);


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