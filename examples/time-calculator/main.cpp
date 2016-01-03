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
    std::cout << "0.00" << std::endl;
    cv::Point2d smallHandTop = cv::Point2d(0, 3);
    cv::Point2d bigHandTop = cv::Point2d(0, 5);
    Time time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    
    // 0.15
    std::cout << "========================================" << std::endl;
    std::cout << "0.15" << std::endl;
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(5, 0);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    
    // 0.30
    std::cout << "========================================" << std::endl;
    std::cout << "0.30" << std::endl;
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(0, -5);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    
    // Between 0.30 and 0.35
    std::cout << "========================================" << std::endl;
    std::cout << "Between 0.30 and 0.35" << std::endl;
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(-1.5, -4);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    
    // 0.45
    std::cout << "========================================" << std::endl;
    std::cout << "0.45" << std::endl;
    smallHandTop = cv::Point2d(0, 3);
    bigHandTop = cv::Point2d(-5, 0);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
    std::cout << "It's " << time.getHour() << ":" << time.getMinute() << "h!" << std::endl;
    
    std::cin.get();
    
    return 0;
}
