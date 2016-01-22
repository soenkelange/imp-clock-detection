//
//  TimeTextOutput.hpp
//  imp-clock-detection
//
//  Created by Sönke Lange on 22.01.16.
//  Copyright © 2016 Sönke Lange. All rights reserved.
//

#ifndef TimeTextOutput_hpp
#define TimeTextOutput_hpp

#include "TimeOutput.hpp"

class TimeTextOutput : public TimeOutput
{
    ~TimeTextOutput();
    void output(cv::Mat& output, const Time& time);
};

#endif /* TimeTextOutput_hpp */
