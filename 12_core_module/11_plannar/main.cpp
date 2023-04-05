#include <iostream>
#include "opencv2/opencv.hpp"

#define CANVAS_SIZE 300
#define OFFSET (short)(CANVAS_SIZE/2)

int main(int agrc, char *argv[])
{
	float 
		x  = 10,
		y  = 60,
		l1 = 40,
		l2 = 40,
		q1,
		q2,
		x1,
		y1,
		x2,
		y2,
		q2a,
		q2b;

	q2 = acos((pow(x, 2) + pow(y, 2) - (pow(l1, 2) + pow(l2, 2)))/(2*l1*l2));

	q2a = l2*sin(q2);
	q2b = l1+l2*cos(q2);

	q1 = atan2(y, x) - atan2(q2a, q2b);

	std::cout << "q1: " << q1*180/M_PI << std::endl;
	std::cout << "q2: " << q2*180/M_PI << std::endl;

  cv::Mat canvas(CANVAS_SIZE, CANVAS_SIZE, CV_8UC3, cv::Scalar(255,255,255));

	cv::line(canvas, cv::Point(OFFSET+x, OFFSET-y), cv::Point(OFFSET+x, OFFSET-y), cv::Scalar(0,0,255), 3);
	cv::line(canvas, cv::Point(OFFSET, 0), cv::Point(OFFSET, CANVAS_SIZE), cv::Scalar(0, 0, 0), 1);
	cv::line(canvas, cv::Point(0, OFFSET), cv::Point(CANVAS_SIZE, OFFSET), cv::Scalar(0, 0, 0), 1);

	x1 = l1 * cos(q1);
	y1 = l1 * sin(q1);

	x2 = x1 + l2 * cos(q1 + q2);
	y2 = y1 + l2 * sin(q1 + q2);

	std::cout << "xy1: " << "("  << round(x1) << ", " << round(y1) << ")"<< std::endl;
	std::cout << "xy2: " << "("  << round(x2) << ", " << round(y2) << ")"<< std::endl;

	cv::line(canvas, cv::Point(OFFSET, OFFSET), cv::Point(OFFSET+x1, OFFSET-y1), cv::Scalar(255, 0, 0), 1);
	cv::line(canvas, cv::Point(OFFSET+x1, OFFSET-y1), cv::Point(OFFSET+x2, OFFSET-y2), cv::Scalar(0, 255, 0), 1);

  cv::resize(canvas, canvas, cv::Size(), 2, 2);
	
	imshow("canvas", canvas);

	cv::waitKey(0);

  return 0;
}
