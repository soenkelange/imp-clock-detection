//
//  TimeTextOutput.cpp
//  imp-clock-detection
//
//  Created by Sönke Lange on 22.01.16.
//  Copyright © 2016 Sönke Lange. All rights reserved.
//

#include "TimeTextOutput.hpp"

TimeTextOutput::~TimeTextOutput()
{
}

void TimeTextOutput::output(cv::Mat& output, const Time &time)
{
    cv::string hourString = std::to_string(time.getHour());
    if (time.getHour() < 10) {
        hourString = "0" + hourString;
    }
    cv::string minuteString = std::to_string(time.getMinute());
    if (time.getMinute() < 10) {
        minuteString = "0" + minuteString;
    }
    cv::string timeString = hourString + ":" + minuteString;
    cv::putText(output, timeString, cv::Point(30,50), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0,255,0));
}