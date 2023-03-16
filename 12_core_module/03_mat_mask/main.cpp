#include <iostream>
#include "opencv2/opencv.hpp"

int main(int agrc, char *argv[])
{
  cv::Mat myImg;
  myImg = cv::imread("../../../img/freya.png");
  //cv::imshow("freya", myImg);
  //cv::waitKey(0);
  cv::Mat freyaGrey = myImg.clone();
  //cv::cvtColor(myImg, freyaGrey, cv::COLOR_BGR2GRAY);
  // cv::Mat kernel = (cv::Mat_<float>(3,3) <<  -0.5, 0.5,  -0.5, 0.5,  0.5, 0.5, -0.5, 0.5,  -0.5);
  cv::Mat kernel = (cv::Mat_<float>(3,3) <<  -0.5, 0.5,  -0.5, 0.5,  2, 0.5, -0.5, 0.5,  -0.5);
  cv::Mat output;
  //
  cv::filter2D(freyaGrey, output, freyaGrey.depth(), kernel);
  // cv::Mat sobelx;
  // cv::Sobel(freyaGrey, sobelx, CV_32F, 1, 0);
  // double minVal, maxVal;
  // minMaxLoc(sobelx, &minVal, &maxVal);
  // cv::Mat draw;
  // // sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
  cv::imshow("freyaFiltered", output);
  cv::waitKey();
  cv::destroyAllWindows();
  return 0;
}
