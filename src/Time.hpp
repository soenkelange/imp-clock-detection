#ifndef Time_hpp
#define Time_hpp

class Time {
    
public:
    Time(double hour, double minute);
    ~Time();
    
    int getHour() const;
    int getMinute() const;
    void output() const;
    
private:
    double _hour;
    double _minute;
};

#endif /* Time_hpp */
