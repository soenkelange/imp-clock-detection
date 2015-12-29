#include <opencv\cv.h>

int main(int argc, char *argv[])
{



	cv::Mat myMat = cv::Mat(16, 8, CV_64F, 0.0);
	std::cout << myMat << std::endl;
	std::cin.get();



	return 0;
}