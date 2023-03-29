#include <iostream>
#include "opencv2/opencv.hpp"

struct HSVComponent
{
	HSVComponent() : h(0), s(0), v(0) {}
	int h, s, v;
};

HSVComponent lower_white_hsv, upper_white_hsv;

int main(int agrc, char *argv[])
{
	cv::Mat image, imageHSV, imageBGR, mask_hsv, mask_bgr, mask_merge, result, blank, canny;
	int canny1, canny2;

	cv::namedWindow("Mask");
	cv::namedWindow("Canny");

	cv::createTrackbar("lower_H", "Mask", &lower_white_hsv.h, 255, 0);
	cv::createTrackbar("lower_S", "Mask", &lower_white_hsv.s, 255, 0);
	cv::createTrackbar("lower_V", "Mask", &lower_white_hsv.v, 255, 0);

	cv::createTrackbar("upper_H", "Mask", &upper_white_hsv.h, 255, 0);
	cv::createTrackbar("upper_S", "Mask", &upper_white_hsv.s, 255, 0);
	cv::createTrackbar("upper_V", "Mask", &upper_white_hsv.v, 255, 0);

	cv::createTrackbar("Canny1", "Canny", &canny1, 300, 0);
	cv::createTrackbar("Canny2", "Canny", &canny2, 300, 0);

	blank = cv::Mat(1, 1, CV_8UC3, cv::Scalar(0, 0, 0));

	cv::Scalar low_white_bgr(60, 60, 60);
	cv::Scalar hight_white_bgr(255, 255, 255);

	//cv::Scalar lower_white(0, 200, 0);
	//cv::Scalar upper_white(255, 255, 255);

	cv::VideoCapture cap;
	cap.open(2);

  while (cv::waitKey(30) != 32)
	{
		cap.read(image);

		cv::GaussianBlur(image, imageBGR, cv::Size(5, 5), 5, 5, cv::BORDER_DEFAULT);
		cv::cvtColor(imageBGR, imageHSV, cv::COLOR_BGR2HSV);

		cv::Scalar lower_white(lower_white_hsv.h, lower_white_hsv.s, lower_white_hsv.v);
		cv::Scalar upper_white(upper_white_hsv.h, upper_white_hsv.s, upper_white_hsv.v);

		cv::inRange(imageBGR, low_white_bgr, hight_white_bgr, mask_bgr);
		cv::inRange(imageHSV, lower_white, upper_white, mask_hsv);

		mask_merge = cv::Mat(1, 1, CV_8UC1, cv::Scalar(0));

		cv::bitwise_and(mask_bgr, mask_hsv, mask_merge, cv::noArray());

		result = blank.clone();

		// cv::erode(result, result, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1)));
		cv::morphologyEx(result, result, cv::MORPH_CLOSE, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1)));

		//cv::Canny(image, canny, canny1, canny2, 5);
		//cv::erode(canny, canny, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1)));
		//cv::morphologyEx(canny, canny, cv::MORPH_CLOSE, getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1)));
		
		cv::imshow("Mask", mask_hsv);
		cv::imshow("MaskMerge", mask_merge);
		//cv::imshow("Canny", canny);
	}
  cv::destroyAllWindows();

  return 0;
}
