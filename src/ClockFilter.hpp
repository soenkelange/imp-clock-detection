#ifndef ClockFilter_h
#define ClockFilter_h

#include <opencv/cv.h>

class ClockFilter
{
public:
    virtual ~ClockFilter() {};
    virtual void process(const cv::Mat& input) = 0;
    virtual cv::Point getBigHandPosition() const = 0;
    virtual cv::Point getSmallHandPosition() const = 0;
    virtual cv::Point getClockCenterPosition() const = 0;
    virtual cv::Point getClockTopPosition() const = 0;
};

#endif /* ClockFilter_h */
