#include <iostream>
#include "opencv2/opencv.hpp"

int main(int agrc, char *argv[])
{
  cv::Mat img, grayscale, hsv, bgr, rgb;
  img = cv::imread(argv[1]);
  //cv::cvtColor(img, grayscale, cv::COLOR_BGR2GRAY);
  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
  //cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);
  //cv::cvtColor(img, rgb, cv::COLOR_BGR2RGB);
  //cv::imshow("Grayscale", grayscale);
  //cv::imshow("HSV", hsv);
  //cv::imshow("BGR", bgr);
  //cv::imshow("RGB", rgb);
  //if (!1 != true)
  //{
  //}
	// std::cout << "Blue:" << std::endl;
	// img = cv::Mat(1, 1, CV_8UC3, cv::Scalar(255, 0, 0));
	// std::cout << img << std::endl;
	// cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
	// std::cout << img << std::endl;

	// std::cout << "Green:" << std::endl;
	// img = cv::Mat(1, 1, CV_8UC3, cv::Scalar(0, 255, 0));
	// std::cout << img << std::endl;
	// cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
	// std::cout << img << std::endl;

	// std::cout << "Red:" << std::endl;
	// img = cv::Mat(1, 1, CV_8UC3, cv::Scalar(0, 0, 255));
	// std::cout << img << std::endl;
	// cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
	// std::cout << img << std::endl;
	// std::cout << "LowWhite" << std::endl;
	// rgb = cv::Mat(1, 1, CV_8UC3, cv::Scalar(255, 255, 255));
	// cv::cvtColor(rgb, rgb, cv::COLOR_BGR2HSV);
	// std::cout << rgb << std::endl;

	// std::cout << "HighWhite" << std::endl;
	// rgb = cv::Mat(1, 1, CV_8UC3, cv::Scalar(80, 80, 80));
	// cv::cvtColor(rgb, rgb, cv::COLOR_BGR2HSV);
	// std::cout << rgb << std::endl;

	//std::cout << "LowWhite" << std::endl;
	//rgb = cv::Mat(1, 1, CV_8UC3, cv::Scalar(15, 50, 180));
	////std::cout << img << std::endl;
	//cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
	//std::cout << img << std::endl;
	//cv::imshow("LowYellow", rgb);

	// std::cout << "HighYellow:" << std::endl;
	// img = cv::Mat(10, 10, CV_8UC3, cv::Scalar(40, 255, 255));
	// //std::cout << img << std::endl;
	// cv::cvtColor(img, img, cv::COLOR_HSV2BGR);
	// //std::cout << img << std::endl;
	// cv::imshow("HighYellow", img);
	
	// bisa masking warna lapangan
	// cv::Mat mask;
	// cv::inRange(hsv, cv::Scalar(40, 128, 128), cv::Scalar(70, 255, 255), mask);
	// cv::Mat result;// = cv::Mat::zeros(img.size(), CV_8UC3);
	// cv::bitwise_and(img, img, result, mask);

	// //cv::imshow("Image", img);
	// //cv::imshow("HSV", hsv);
	// cv::imshow("Mask", mask);
	// cv::imshow("AND", result);
	// cv::bitwise_xor(img, result, result);
	// cv::imshow("XOR", result);

	cv::Mat mask;
	cv::inRange(img, cv::Scalar(200, 200, 200), cv::Scalar(255, 255, 255), mask);
	cv::Mat result;
	cv::bitwise_and(img, img, result, mask);

	cv::imshow("Mask", mask);
	cv::imshow("AND", result);
	//cv::bitwise_xor(img, result, result);
	//cv::imshow("XOR", result);
	


  while (cv::waitKey(30) != 32);
  cv::destroyAllWindows();
  return 0;
}
