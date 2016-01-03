#ifndef Time_hpp
#define Time_hpp

#include <stdio.h>

class Time {
    
public:
    Time(int hour, int minute);
    ~Time();
    
    int getHour();
    int getMinute();
    
private:
    int _hour;
    int _minute;
};

#endif /* Time_hpp */
