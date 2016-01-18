//
//  TimeLogger.hpp
//  imp-clock-detection
//
//  Created by Sönke Lange on 18.01.16.
//  Copyright © 2016 Sönke Lange. All rights reserved.
//

#ifndef TimeLogger_hpp
#define TimeLogger_hpp

#include "TimeOutput.hpp"

class TimeLogger : public TimeOutput
{
    ~TimeLogger();
    void output(const Time& time);
};

#endif /* TimeLogger_hpp */
