#include "Time.hpp"

Time::Time(int hour, int minute) :
    _hour(hour),
    _minute(minute)
{
}

Time::~Time()
{
}

int Time::getHour()
{
    return _hour;
}

int Time::getMinute()
{
    return _minute;
}