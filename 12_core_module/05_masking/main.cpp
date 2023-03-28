#include <iostream>
#include "opencv2/opencv.hpp"

int main(int agrc, char *argv[])
{
  cv::Mat img, grayscale, hsv, bgr, rgb, hls;
  //img = cv::imread(argv[1]);
  //cv::cvtColor(img, grayscale, cv::COLOR_BGR2GRAY);
  //cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
  //cv::cvtColor(img, hls, cv::COLOR_BGR2HLS);
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
	//rgb = cv::Mat(1, 1, CV_8UC3, cv::Scalar(0x36, 0x2a, 0x28));
	//std::cout << img << std::endl;
	//cv::cvtColor(rgb, rgb, cv::COLOR_BGR2HSV);
	//std::cout << rgb << std::endl;
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

	// cv::Mat mask;
	// cv::inRange(img, cv::Scalar(200, 200, 200), cv::Scalar(255, 255, 255), mask);
	// cv::Mat result;
	// cv::bitwise_and(img, img, result, mask);

	// cv::imshow("Mask", mask);
	// cv::imshow("AND", result);
	// cv::imshow("HLS", hls);
	//cv::Mat a;
	////int kernelSize = 2;
	////cv::Mat mask;
	////cv::inRange(img, cv::Scalar(200, 200, 200), cv::Scalar(255, 255, 255), mask);
	////cv::erode(mask, mask, getStructuringElement(cv::MORPH_RECT, cv::Size(2*kernelSize+1, 2*kernelSize+1), cv::Point(kernelSize, kernelSize)));
	////cv::dilate(mask, mask, getStructuringElement(cv::MORPH_RECT, cv::Size(2*kernelSize+1, 2*kernelSize+1), cv::Point(kernelSize, kernelSize)));
	////std::cout << sqrt(cv::countNonZero(mask)) << std::endl;
	////// cv::findNonZero(mask, grayscale);
	////std::cout << mask.channels() << std::endl;
	//////std::cout << grayscale;
	//////cv::cvtColor(mask, cvt, )

	////// cv::Mat result;
	//////cv::cvtColor(cv::Scalar(0x36, 0x2a, 0x28), a, cv::COLOR_BGR2HSV);
	//////cv::bitwise_xor(img, result, result);
	////cv::imshow("XOR", mask);

	cv::Mat idk = cv::Mat(3, 3, CV_8UC1, cv::Scalar(1));
	idk[0] = 1;
	cv::findNonZero(idk, grayscale);
	std::cout << idk.channels() << std::endl;
	std::cout << grayscale;
	cv::imshow("idk", idk);

  while (cv::waitKey(30) != 32);

  cv::destroyAllWindows();
  return 0;
}
