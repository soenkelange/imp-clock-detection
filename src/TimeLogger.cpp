//
//  TimeLogger.cpp
//  imp-clock-detection
//
//  Created by Sönke Lange on 18.01.16.
//  Copyright © 2016 Sönke Lange. All rights reserved.
//

#include "TimeLogger.hpp"

#include <iostream>

TimeLogger::~TimeLogger()
{
}

void TimeLogger::output(const Time &time)
{
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "!" << std::endl;
}