#include "cvWrapper.h"

Cmd keyboard() {
	char key = cv::waitKey(30);
	Cmd cmd = nothing;
	char upperKey = static_cast<char>(toupper(key));

	//ESC
	if(key == 27) {
		std::cout << "ESC" << std::endl;
		cmd = Esc;
	}
	else if (upperKey == 'E') {
		cmd = Edit;
	}
	else if (upperKey == 'S') {
		cmd = Save;
	}
	
	return cmd;
}

void faceDetector(cv::Mat src, Cmd mode) {
	std::string faceHarr = "C:\\OpenCV-2.4\\opencv\\data\\haarcascades\\haarcascade_frontalface_default.xml";
	cv::CascadeClassifier harrCascade;
	harrCascade.load(faceHarr);

	cv::Mat original = src.clone();
	cv::Mat gray;
	cv::cvtColor(original, gray, CV_BGR2GRAY);

	std::vector<cv::Rect_<int>> faces;
	clock_t time = clock();

	harrCascade.detectMultiScale(gray, faces);
	for(int i = 0; i < faces.size();i++)
	{
		cv::Rect faceRect = faces[i];
		
		if(mode == Edit) {
			//int posX = std::max(faceRect.tl().x - 10, 0);
			//int posY = std::max(faceRect.tl().y - 10, 0);
			std::cout << "patient...\n";
			int posX = faceRect.tl().x;
			int posY = faceRect.tl().y;
			std::vector<cv::Point> arraypoint;
			
			if(facialpoint( src , faces , arraypoint)) {
				for( int i = 0 ; i < 49 ; i++ ) {
					if(!arraypoint.empty()) {
						cv::Point p1 = arraypoint.at(i);
						cv::circle( original , p1 , 1, cv::Scalar(0,255,0) , -1 );
					}
				}
			}

			std::string text = "face detect";
			cv::rectangle(original, faceRect, cv::Scalar(255,0,0),2);
			cv::putText(original, text, cv::Point(posX, posY), cv::FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);

			cv::imshow("face detection", original);
			std::cout << "time elapse:" << clock() - time;
			cv::imwrite("facedetect.bmp", original);
			cv::waitKey(0);
		}
		else if(mode == Save) {

		}
	}
}