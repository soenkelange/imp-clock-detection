#include <opencv/cv.h>
#include "TimeCalculator.hpp"
#include "Time.hpp"

int main(int argc, char *argv[])
{
    TimeCalculator timeCalculator = TimeCalculator();
    cv::Point2d clockMiddle = cv::Point2d(0, 0);
    cv::Point2d clockTop = cv::Point2d(0, 6);
    
    // 0.00
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.00" << std::endl;
    clockTop = cv::Point2d(0, 6);
    cv::Point2d smallHandTop = cv::Point2d(0, 3);
    cv::Point2d bigHandTop = cv::Point2d(0, 5);
    Time time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // 0.15
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.15" << std::endl;
    clockTop = cv::Point2d(0, 6);
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(5, 0);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // 0.30
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.30" << std::endl;
    clockTop = cv::Point2d(0, 6);
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(0, -5);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // Between 0.35 and 0.40
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: Between 0.35 and 0.40" << std::endl;
    clockTop = cv::Point2d(0, 6);
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(-4, -4);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // Between 0.50 and 0.55
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: Between 0.50 and 0.55" << std::endl;
    clockTop = cv::Point2d(0, 6);
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(-4, 4);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // 0.45
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.45" << std::endl;
    clockTop = cv::Point2d(0,6);
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(-5, 0);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // 3.15
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 3.15" << std::endl;
    clockTop = cv::Point2d(-6,0);
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(0, 5);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // 6.15
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 6.15" << std::endl;
    clockTop = cv::Point2d(0,6);
    smallHandTop = cv::Point2d(0, -3);
    bigHandTop = cv::Point2d(5, 0);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // 9.45
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 9.45" << std::endl;
    clockTop = cv::Point2d(-6,0);
    smallHandTop = cv::Point2d(0, -3);
    bigHandTop = cv::Point2d(0, -5);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    
    // Between 10.50 and 10.55
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: Between 10.50 and 10.55" << std::endl;
    clockTop = cv::Point2d(0, 6);
    smallHandTop = cv::Point2d(-4, 4);
    bigHandTop = cv::Point2d(-4, 4);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    // Between 9.45
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 9.45" << std::endl;
    clockTop = cv::Point2d(0, -6);
    smallHandTop = cv::Point2d(3, 0);
    bigHandTop = cv::Point2d(5, 0);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    time.output();
    
    std::cin.get();
    
    return 0;
}
