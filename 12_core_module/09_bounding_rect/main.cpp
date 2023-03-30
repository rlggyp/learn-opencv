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

	int maxArea;
	int idx;

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

		cv::findContours(mask, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

		maxArea = 1000;
		idx = -2;

		
		std::vector<std::vector<cv::Point>> hull(contours.size());
		std::vector<std::vector<cv::Point>> contours_poly(contours.size());
		std::vector<cv::Rect> boundRect(contours.size());
		std::vector<cv::Point2f>centers( contours.size() );
		std::vector<float>radius( contours.size() );

		for (int i = 0; i < contours.size(); ++i)
		{
			cv::convexHull(contours[i], hull[i]);
			cv::approxPolyDP(contours[i], contours_poly[i], 3, true);
			boundRect[i] = cv::boundingRect(contours_poly[i]);
   		cv::minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
		}

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
		{
			cv::drawContours(frame, contours, idx, cv::Scalar(255, 0, 0), 4);
			cv::drawContours(frame, hull, idx, cv::Scalar(255, 0, 255), 4);
			cv::rectangle(frame, boundRect[idx].tl(), boundRect[idx].br(), cv::Scalar(0, 255, 255), 4);

			cv::Point_<int> top = boundRect[idx].tl();
			cv::Point_<int> bottom = boundRect[idx].br();
			int radius_1 = (bottom.y - top.y)/2;
			int radius_2 = (bottom.x - top.x)/2;
			int radius_ = radius_1 > radius_2 ? radius_1 : radius_2;

			cv::circle(frame, cv::Point_<int>((top.x + bottom.x)/2, (top.y + bottom.y)/2), radius_, cv::Scalar(0, 255, 0), 4);
			cv::circle(frame, centers[idx], (int)radius[idx], 2);
		}

		cv::imshow("mask", frame);
	}

	cap.release();
  cv::destroyAllWindows();

  return 0;
}
