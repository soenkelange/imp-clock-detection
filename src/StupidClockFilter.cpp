#include "StupidClockFilter.hpp"
#include <opencv/highgui.h>

StupidClockFilter::~StupidClockFilter()
{
}

void StupidClockFilter::process(const cv::Mat& input)
{
    cv::imshow("Debug", input);
}

cv::Point StupidClockFilter::getBigHandPosition() const
{
    return cv::Point(4,0);
}

cv::Point StupidClockFilter::getSmallHandPosition() const
{
    return cv::Point(-4,0);
}

cv::Point StupidClockFilter::getClockCenterPosition() const
{
    return cv::Point(0,0);
}

cv::Point StupidClockFilter::getClockTopPosition() const
{
    return cv::Point(0,-6);
}