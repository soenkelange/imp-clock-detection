#include "StupidClockFilter.hpp"
#include "TimeCalculator.hpp"
#include "TimeLogger.hpp"

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

enum VideoSource {
    NONE,
    CAMERA,
    VIDEO_FILE
};

const cv::string& sourceWindow = "Source";

VideoSource readVideoSource();
cv::string readVideoFilename();

int main(int argc, char *argv[])
{
    VideoSource videoSource = readVideoSource();
    cv::VideoCapture videoCapture;
    if (videoSource == CAMERA) {
        videoCapture = cv::VideoCapture(0);
    } else if (videoSource == VIDEO_FILE) {
        cv::string filename = readVideoFilename();
        videoCapture = cv::VideoCapture(filename);
    }
    
    if (!videoCapture.isOpened()) {
        std::cout << "Could not open VideoCaptur" << std::endl;
        return -1;
    }
    
    ClockFilter* filter = new StupidClockFilter; // TODO: Add correct ClockFilter here
    TimeCalculator* timeCalculator = new TimeCalculator();
    TimeOutput* timeOutput = new TimeLogger(); // TODO: Add correct TimeOutput here
    
    while (1) {
        cv::Mat inputFrame;
        videoCapture.read(inputFrame);
        
        // filter clock
        filter->process(inputFrame);
        cv::Point2d clockMiddle = filter->getClockCenterPosition();
        cv::Point2d clockTop = filter->getClockTopPosition();
        cv::Point2d bigHandTop = filter->getBigHandPosition();
        cv::Point2d smallHandTop = filter->getSmallHandPosition();
        
        // calculate time
        Time time = timeCalculator->calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
        
        // output time
        timeOutput->output(time);
        
        cv::imshow(sourceWindow, inputFrame);
        
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }
    delete filter;
    delete timeCalculator;
    delete timeOutput;
	return 0;
}

VideoSource readVideoSource()
{
    int selectedVideoSource = NONE;
    while((selectedVideoSource != CAMERA) && (selectedVideoSource != VIDEO_FILE)) {
        std::cout << "Please select the video source:" << std::endl;
        std::cout << "(1) Camera0" << std::endl;
        std::cout << "(2) File" << std::endl;
        std::cin >> selectedVideoSource;
    }
    if (selectedVideoSource == CAMERA) {
        return CAMERA;
    } else if (selectedVideoSource == VIDEO_FILE) {
        return VIDEO_FILE;
    } {
        return NONE;
    }
}

cv::string readVideoFilename() {
    std::cout << "Please input the path to the video file:" << std::endl;
    cv::string filename;
    std::cin >> filename;
    return filename;
}

