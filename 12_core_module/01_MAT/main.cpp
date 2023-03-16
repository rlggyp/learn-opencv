#include <iostream>
#include "opencv2/opencv.hpp"

int main(int agrc, char *argv[])
{
  cv::Mat A, C;
  A = cv::imread("../../../img/freya.png");
  //std::cout << A << std::endl;

  // cv::Mat B(A);
  // C = A;
  // cv::Mat D(A, cv::Rect(10, 10, 50, 50));
  // cv::Mat E = A(cv::Range(10, 60), cv::Range(10, 60));
  // cv::imshow("freya", D);
  // cv::waitKey(0);
  // cv::imshow("freya2", C);
  // cv::waitKey(0);
  // cv::imshow("freya3", E);
  // cv::waitKey(0);
  // cv::Mat G;
  // E.copyTo(G);
  // cv::imshow("freya4", G);
  // cv::waitKey(0);
  // cv::destroyAllWindows();

  cv::Mat M(1, 1, CV_8UC3, cv::Scalar(0,0,255));
  std::cout << "M : " << std::endl << M << std::endl << std::endl;
  std::cout << std::endl;
  cv::Mat N(1, 1, CV_16UC1, cv::Scalar(12));
  std::cout << "N : " << std::endl << N << std::endl << std::endl;
  std::cout << std::endl;
  M.create(2,2, CV_8UC(2));
  std::cout << "M : " << std::endl << M << std::endl << std::endl;
  cv::Mat E = cv::Mat::eye(4, 4, CV_64F);
  std::cout << "E = " << std::endl << " " << E << std::endl << std::endl;
  cv::Mat O = cv::Mat::ones(2, 2, CV_32F);
  std::cout << "O = " << std::endl << " " << O << std::endl << std::endl;
  cv::Mat Z = cv::Mat::zeros(3,3, CV_8UC1);
  std::cout << "Z = " << std::endl << " " << Z << std::endl << std::endl;
  std::cout << M.cols << ", " << M.rows <<std::endl;
  return 0;
}
