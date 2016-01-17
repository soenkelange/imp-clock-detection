#include "Time.hpp"
#include <iostream>

Time::Time(double hour, double minute) :
    _hour(hour),
    _minute(minute)
{
}

Time::~Time()
{
}

int Time::getHour() const
{
    return _hour;
}

int Time::getMinute() const
{
    return _minute;
}

void Time::output() const
{
    std::cout.precision(2);
    std::cout << "Time: " << std::fixed << _hour << ":" << std::fixed <<_minute << std::endl;
}