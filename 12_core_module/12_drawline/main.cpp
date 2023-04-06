#include <iostream>
#include <unistd.h>
#include "opencv2/opencv.hpp"

#define CANVAS_SIZE 100
#define OFFSET (short)(CANVAS_SIZE/2)

#define Deg2Rad(angle) (angle*M_PI/180)

int main(int agrc, char *argv[])
{
	float 
		x,
		y,
		heading = 0,
		line_len = 40;

	cv::Mat canvas(CANVAS_SIZE, CANVAS_SIZE, CV_8UC3, cv::Scalar(255,255,255));

	cv::line(canvas, cv::Point(OFFSET, 0), cv::Point(OFFSET, CANVAS_SIZE), cv::Scalar(0, 0, 0), 1);
	cv::line(canvas, cv::Point(0, OFFSET), cv::Point(CANVAS_SIZE, OFFSET), cv::Scalar(0, 0, 0), 1);

	char key;

	while (key != 27)
	{
		key = cv::waitKey(5);

		canvas = cv::Mat(CANVAS_SIZE, CANVAS_SIZE, CV_8UC3, cv::Scalar(255,255,255));

		cv::line(canvas, cv::Point(OFFSET, 0), cv::Point(OFFSET, CANVAS_SIZE), cv::Scalar(0, 0, 0), 1);
		cv::line(canvas, cv::Point(0, OFFSET), cv::Point(CANVAS_SIZE, OFFSET), cv::Scalar(0, 0, 0), 1);

		x = sin(Deg2Rad(heading)) * line_len;
		y = cos(Deg2Rad(heading)) * line_len;

		cv::line(canvas, cv::Point(OFFSET, OFFSET), cv::Point(OFFSET+x, OFFSET-y), cv::Scalar(255, 0, 0), 2);

		if (--heading == -180)
			heading = 180;

		cv::resize(canvas, canvas, cv::Size(), 2, 2);

		imshow("canvas", canvas);
	}
	

  return 0;
}
