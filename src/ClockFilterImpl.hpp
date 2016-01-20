#ifndef ClockFilterImpl_hpp
#define ClockFilterImpl_hpp

#include <stdio.h>
#include "ClockFilter.h"

class ClockFilterImpl : public ClockFilter
{
public:
	~ClockFilterImpl();
	void process(const cv::Mat& input);
	cv::Point getBigHandPosition() const;
	cv::Point getSmallHandPosition() const;
	cv::Point getClockCenterPosition() const;
	cv::Point getClockTopPosition() const;
};

#endif /* ClockFilterImpl_hpp */
