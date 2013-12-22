#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string.h>
#include <time.h>
#include "facialpoint.h"

enum Cmd {
	nothing,
	Edit,
	Esc,
	Save
};
Cmd keyboard();
void faceDetector(cv::Mat src, Cmd mode);