#include "StupidClockFilter.hpp"
#include <opencv/highgui.h>

ClockFilter::~ClockFilter()
{
}

void ClockFilter::process(const cv::Mat& input)
{
	cv::imshow("Debug", input);
}

cv::Point ClockFilter::getBigHandPosition() const
{
	return cv::Point(4, 0);
}

cv::Point ClockFilter::getSmallHandPosition() const
{
	return cv::Point(-4, 0);
}

cv::Point ClockFilter::getClockCenterPosition() const
{
	return cv::Point(0, 0);
}

cv::Point ClockFilter::getClockTopPosition() const
{
	return cv::Point(0, -6);
}