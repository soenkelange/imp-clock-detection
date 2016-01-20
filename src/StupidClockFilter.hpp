#ifndef StupidClockFilter_hpp
#define StupidClockFilter_hpp

#include <stdio.h>
#include "ClockFilter.h"

class StupidClockFilter : public ClockFilter
{
public:
    ~StupidClockFilter();
    void process(const cv::Mat& input);
    cv::Point getBigHandPosition() const;
    cv::Point getSmallHandPosition() const;
    cv::Point getClockCenterPosition() const;
    cv::Point getClockTopPosition() const;
};

#endif /* StupidClockFilter_hpp */
