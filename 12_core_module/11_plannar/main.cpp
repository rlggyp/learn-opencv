#include <iostream>
#include "opencv2/opencv.hpp"

int main(int agrc, char *argv[])
{
	float x, y;
	x = 10;
	y = 60;

	float l1, l2, q1, q2, q1rad, q2rad;
	l1 = 40;
	l2 = 40;

	q2rad = (pow(x, 2) + pow(y, 2) - (pow(l1, 2) + pow(l2, 2)))/(2*l1*l2);
	q2 = acos(q2rad);

	q1 = atan((float)y/x) - atan((l2*sin(q2))/(l1+l2*cos(q2)));

  cv::Mat canvas(400, 400, CV_8UC3, cv::Scalar(255,255,255));
	cv::line(canvas, cv::Point(200+x, 200-y), cv::Point(200+x, 200-y), cv::Scalar(0,0,255), 6);
	cv::line(canvas, cv::Point(200, 0), cv::Point(200, 400), cv::Scalar(0, 0, 0), 1);
	cv::line(canvas, cv::Point(0, 200), cv::Point(400, 200), cv::Scalar(0, 0, 0), 1);

	cv::line(canvas, cv::Point(200, 200), cv::Point(200+l1*cos(q1), 200-l1*sin(q1)), cv::Scalar(255, 0, 0), 2);
	cv::line(canvas, cv::Point(200+l1*cos(q1), 200-l1*sin(q1)), cv::Point(200+l1*cos(q1)+l2*cos(q1 + q2), 200-l1*sin(q1)-l2*sin(q1 + q2)), cv::Scalar(0, 255, 0), 2);

	std::cout << "q1: " << q1*180/M_PI << std::endl;
	std::cout << "q2: " << q2*180/M_PI << std::endl;

	imshow("canvas", canvas);
	cv::waitKey(0);
  return 0;
}
