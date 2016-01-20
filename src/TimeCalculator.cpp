//
// Calculate the cutting angle between two vectors
// http://www.frustfrei-lernen.de/mathematik/schnittwinkel-zweier-geraden.html
//

#include "TimeCalculator.hpp"
#include <stdio.h>
#include <math.h>

TimeCalculator::TimeCalculator()
{
}

TimeCalculator::~TimeCalculator()
{
}

Time TimeCalculator::calculcateTime(cv::Point2d clockMiddle, cv::Point2d clockTop, cv::Point2d bigHandTop, cv::Point2d smallHandTop)
{
    clockTop = transformCoordinates(clockMiddle, clockTop);
    bigHandTop = transformCoordinates(clockMiddle, bigHandTop);
    smallHandTop = transformCoordinates(clockMiddle, smallHandTop);
    clockMiddle = transformCoordinates(clockMiddle, clockMiddle);
    
    double clockTopAndSmallHandTop = calculateDegress(clockTop, smallHandTop);
    int smallHandPosition = (clockMiddle.x - clockTop.x) * (smallHandTop.y - clockTop.y) - (clockMiddle.y - clockTop.y) * (smallHandTop.x - clockTop.x);
    std::cout << "Small Hand Position: " << smallHandPosition << std::endl;
    if (smallHandPosition < 0) {
        clockTopAndSmallHandTop = 180 + (180 - clockTopAndSmallHandTop);
    }
    double degressPerHour = 360 / 12;
    double hour = clockTopAndSmallHandTop / degressPerHour;
    
    double clockTopAndBigHandTop = calculateDegress(clockTop, bigHandTop);
    int bigHandPosition = (clockMiddle.x - clockTop.x) * (bigHandTop.y - clockTop.y) - (clockMiddle.y - clockTop.y) * (bigHandTop.x - clockTop.x);
    std::cout << "Big Hand Position: " << bigHandPosition << std::endl;
    if (bigHandPosition < 0) {
        clockTopAndBigHandTop = 180 + (180 - clockTopAndBigHandTop);
    }
    double degressPerMinute = 360 / 60;
    double minute = clockTopAndBigHandTop / degressPerMinute;
    return Time(hour, minute);
}

double TimeCalculator::calculateDegress(cv::Point2d a1, cv::Point2d a2)
{
    double scalar = calculateScalarProduct(a1, a2);
    double lengthA1 = calculateVectorLength(a1);
    double lengthA2 = calculateVectorLength(a2);
    
    double p = (scalar / (lengthA1 * lengthA2) );
    double r = acos( p );
    return radian2Degress(r);
}

double TimeCalculator::calculateScalarProduct(cv::Point2d a1, cv::Point2d a2)
{
    return ((a1.x * a2.x) + (a1.y * a2.y));
}

double TimeCalculator::calculateVectorLength(cv::Point2d v)
{
    return sqrt( pow(v.x, 2) + pow(v.y, 2) );
}

double TimeCalculator::radian2Degress(double d)
{
    std::cout << "radian2Degress: " << d << std::endl;
    return d * 180 / M_PI;
}

cv::Point2d TimeCalculator::transformCoordinates(cv::Point2d zero, cv::Point2d point)
{
    point = point - zero;
    point.y = point.y * -1;
    return point;
}
