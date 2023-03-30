#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"

struct HSVComponent
{
	HSVComponent() : h(0), s(0), v(0) {}
	int h, s, v;
};

int main(int agrc, char *argv[])
{
	cv::Mat frame, frameHSV, mask;
	cv::VideoCapture cap;

	cap.open(0);
	cap.read(frame);

	std::vector<cv::Vec4i> hierarchy;
	std::vector<std::vector<cv::Point>> contours;

	cv::namedWindow("frame");
	cv::namedWindow("mask");

	HSVComponent lower_color_hsv, upper_color_hsv;

	cv::createTrackbar("LOWER_H", "mask", &lower_color_hsv.h, 179);
	cv::createTrackbar("LOWER_S", "mask", &lower_color_hsv.s, 255);
	cv::createTrackbar("LOWER_V", "mask", &lower_color_hsv.v, 255);

	cv::createTrackbar("UPPER_H", "mask", &upper_color_hsv.h, 179);
	cv::createTrackbar("UPPER_S", "mask", &upper_color_hsv.s, 255);
	cv::createTrackbar("UPPER_V", "mask", &upper_color_hsv.v, 255);

	cv::Scalar lower_color(0, 0, 0);
	cv::Scalar upper_color(0, 0, 0);

	int maxArea = 0;
	int idx = -2;

	while (cv::waitKey(1) != 27)
	{
		cap.read(frame);
		cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);

		hierarchy.clear();
		contours.clear();

		cv::GaussianBlur(frameHSV, frameHSV, cv::Size(3, 3), -1, -1);

		lower_color = cv::Scalar(lower_color_hsv.h, lower_color_hsv.s, lower_color_hsv.v);
		upper_color = cv::Scalar(upper_color_hsv.h, upper_color_hsv.s, upper_color_hsv.v);

		cv::inRange(frameHSV, lower_color, upper_color, mask);

		cv::morphologyEx(mask, mask, cv::MORPH_OPEN, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));
		cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3)));

		cv::findContours(mask, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

		maxArea = 1000;
		idx = -2;

		for (int i = 0; i < contours.size(); ++i)
		{
			static int temp;

			temp = fabs(cv::contourArea(contours[i]));
			if (temp > maxArea)
			{
				maxArea = temp;
				idx = i;
			}
		}

		if (idx != -2)
			cv::drawContours(frame, contours, idx, cv::Scalar(255, 0, 0), 4);

		cv::imshow("mask", frame);
	}

	cap.release();
  cv::destroyAllWindows();

  return 0;
}
