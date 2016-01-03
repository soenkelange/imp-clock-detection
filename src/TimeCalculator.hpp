#ifndef TimeCalculator_hpp
#define TimeCalculator_hpp

#include <stdio.h>
#include <opencv/cv.h>
#include "Time.hpp"

class TimeCalculator {
    
public:
    TimeCalculator();
    ~TimeCalculator();
    
    Time calculcateTime(cv::Point2d clockMiddle, cv::Point2d clockTop, cv::Point2d bigHandTop, cv::Point2d smallHandTop);
    
private:
    double calculateDegress(cv::Point2d a1, cv::Point2d a2);
    double calculateScalarProduct(cv::Point2d a1, cv::Point2d a2);
    double calculateVectorLength(cv::Point2d v);
    double radian2Degress(double d);
};

#endif /* TimeCalculator_hpp */
