#include "ClockFilterImpl.hpp"
#include "TimeCalculator.hpp"
#include "TimeTextOutput.hpp"

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>

enum VideoSource {
    NONE,
    CAMERA,
    VIDEO_FILE
};

const cv::string& sourceWindow = "Source";
const cv::string& outputWindow = "Output";

int readCameraSelection();
VideoSource readVideoSource();
cv::string readVideoFilename();

int main(int argc, char *argv[])
{
    VideoSource videoSource = readVideoSource();
    cv::VideoCapture videoCapture;
    if (videoSource == CAMERA) {
        int camera = readCameraSelection();
        videoCapture = cv::VideoCapture(camera);
    } else if (videoSource == VIDEO_FILE) {
        cv::string filename = readVideoFilename();
        videoCapture = cv::VideoCapture(filename);
    }
    
    if (!videoCapture.isOpened()) {
        std::cout << "Could not open VideoCaptur" << std::endl;
        return -1;
    }
    
    ClockFilter* filter = new ClockFilterImpl;
    TimeCalculator* timeCalculator = new TimeCalculator();
    TimeOutput* timeOutput = new TimeTextOutput;
    
    
    bool paused = false;
    bool debug = false;
    while (1) {
        if (!paused) {
            cv::Mat inputFrame;
            videoCapture.read(inputFrame);
            if (inputFrame.empty()) {
                break;
            }
            
            cv::Mat outputFrame;
            inputFrame.copyTo(outputFrame);
            
            // filter clock
            filter->process(inputFrame);
            cv::Point2d clockMiddle = filter->getClockCenterPosition();
            cv::Point2d clockTop = filter->getClockTopPosition();
            cv::Point2d bigHandTop = filter->getBigHandPosition();
            cv::Point2d smallHandTop = filter->getSmallHandPosition();
            
            // calculate time
            Time time = timeCalculator->calculcateTime(clockMiddle, clockTop, bigHandTop, smallHandTop);
            
            if (debug) {
                cv::circle(outputFrame, clockMiddle, 30, cv::Scalar(255,0,0));            // BLUE
                cv::putText(outputFrame, "M", clockMiddle, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255,0,0));
                cv::circle(outputFrame, clockTop, 30, cv::Scalar(0,255,0));         // GREEN
                cv::putText(outputFrame, "T", clockTop, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0,255,0));
                cv::circle(outputFrame, smallHandTop, 30, cv::Scalar(0,0,255));            // RED
                cv::putText(outputFrame, "S", smallHandTop, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0,0,255));
                cv::circle(outputFrame, bigHandTop, 30, cv::Scalar(0,255,255));        // YELLOW
                cv::putText(outputFrame, "B", bigHandTop, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0,255,255));
            }
            
            // output time
            timeOutput->output(outputFrame, time);
            
            cv::imshow(sourceWindow, inputFrame);
            cv::imshow(outputWindow, outputFrame);
        }
        
        int waitKey = cv::waitKey(30);
        if(waitKey == -1) {
            continue;
        } else if (waitKey == 113) { // q
            break;
        } else if (waitKey == 112) {
            paused = !paused;
        } else if (waitKey == 100){
            debug = !debug;
        }
    }
    delete filter;
    delete timeCalculator;
    delete timeOutput;
	return 0;
}

int readCameraSelection()
{
    int selectedCamera = 0;
    std::cout << "Please enter the camera number or use default one:" << std::endl;
    std::cin >> selectedCamera;
    return selectedCamera;
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

