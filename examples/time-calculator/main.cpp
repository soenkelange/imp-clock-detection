#include <opencv/cv.h>
#include "TimeCalculator.hpp"
#include "Time.hpp"

int main(int argc, char *argv[])
{
    TimeCalculator timeCalculator = TimeCalculator();

    
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.14" << std::endl;
    cv::Point clockMiddle = cv::Point(166,190);
    cv::Point clockTop = cv::Point(369,231);
    cv::Point smallHand = cv::Point(282,208);
    cv::Point bigHand = cv::Point(391,120);
    Time time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHand, smallHand);
    std::cout << "Actual: " << time.getHour() << ":" << time.getMinute() << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.14" << std::endl;
    clockTop = cv::Point(367,442);
    clockMiddle = cv::Point(368,225);
    smallHand = cv::Point(370,305);
    bigHand = cv::Point(215,222);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHand, smallHand);
    std::cout << "Actual: " << time.getHour() << ":" << time.getMinute() << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.14" << std::endl;
    clockTop = cv::Point(375,410);
    clockMiddle = cv::Point(374,205);
    smallHand = cv::Point(377,277);
    bigHand = cv::Point(265,206);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHand, smallHand);
    std::cout << "Actual: " << time.getHour() << ":" << time.getMinute() << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "Expected: 0.14" << std::endl;
    clockTop = cv::Point(465,286);
    clockMiddle = cv::Point(281,255);
    smallHand = cv::Point(366,266);
    bigHand = cv::Point(267,349);
    time = timeCalculator.calculcateTime(clockMiddle, clockTop, bigHand, smallHand);
    std::cout << "Actual: " << time.getHour() << ":" << time.getMinute() << std::endl;
    
    std::cin.get();
    
    return 0;
}
