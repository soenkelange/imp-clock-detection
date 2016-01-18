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


class TimeOutput
{
public:
    virtual ~TimeOutput() = 0;
    virtual void output(const Time& time) = 0;
};

#endif /* TimeOutput_h */
