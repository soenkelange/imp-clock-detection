//
//  TimeOutput.h
//  imp-clock-detection
//
//  Created by Sönke Lange on 18.01.16.
//  Copyright © 2016 Sönke Lange. All rights reserved.
//

#ifndef TimeOutput_h
#define TimeOutput_h

#include "Time.hpp"
#include <opencv/cv.h>


class TimeOutput
{
public:
    virtual ~TimeOutput() {};
    virtual void output(cv::Mat& output, const Time& time) = 0;
};

#endif /* TimeOutput_h */
