#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <math.h>
#include <opencv2/core/hal/intrin.hpp>
#include <opencv2/core/utility.hpp>


int main(int argc, char *argv[])
{
  /* ========== Basic Mat Operation ========== */
  // cv::Mat img;
  // img = cv::imread(argv[1], cv::IMREAD_COLOR);
  // cv::imshow("Color", img);
  // img = cv::imread(argv[1], cv::IMREAD_ANYDEPTH);
  // cv::imshow("AnyDepth", img);
  // img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  // cv::imshow("Grayscale", img);
  // img = cv::imread(argv[1], cv::IMREAD_REDUCED_COLOR_2);
  // cv::imshow("ReducedColor2", img);
  // img = cv::imread(argv[1], cv::IMREAD_REDUCED_COLOR_4);
  // cv::imshow("ReducedColor4", img);
  // img = cv::imread(argv[1], cv::IMREAD_REDUCED_COLOR_8);
  // cv::imshow("ReducedColor8", img);
  // img = cv::imread(argv[1], cv::IMREAD_UNCHANGED);
  // cv::imshow("Unchanged", img);

  // cv::Mat A (img, cv::Rect(10, 10, 100, 100)); // using rectangle
  // cv::imshow("A", A);
  // cv::Mat B(A); // use copy constructroe
  // cv::Mat C;
  // C = A; // use assignment operator
  // cv::imshow("C1", C);
  // img = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  // A = img.clone();
  // cv::imshow("C2", C);
  // std::cout << C.channels() << " " << (C.depth() == CV_8UC(1)) << std::endl;
  // std::cout << A.channels() << " " << (A.depth() == CV_8UC(1)) << std::endl;
  // std::cout << img.channels() << " " << (img.depth() == CV_8UC(2)) << std::endl;

  /* ========== Blend Image ========== */
  // cv::Mat img, img2, blendedImage;
  // int alpha = 0.5, beta = 0.5;

  // img  = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  // cv::resize(cv::imread(argv[2], cv::IMREAD_GRAYSCALE), img2, cv::Size(), 0.25, 0.25);
  // img2 = cv::Mat(img2, cv::Rect(img2.cols/4, img2.rows/4, img.cols, img.rows));
  
  // std::cerr << img.size() << std::endl;
  // std::cerr << img2.size() << std::endl;

  // if (img.empty())
  // {
  //   std::cerr << "Error cant load image 1" << std::endl;
  //   return EXIT_FAILURE;
  // }

  // if (img2.empty())
  // {
  //   std::cerr << "Error cant load image 2" << std::endl;
  //   return EXIT_FAILURE;
  // }

  // cv::addWeighted(img, (double)alpha/10.0, img2, (double)beta/10.0, 0.0, blendedImage);
  // cv::namedWindow("BlendedImage", cv::WINDOW_NORMAL);

  // cv::createTrackbar("Alpha", "BlendedImage", &alpha, 10);
  // cv::createTrackbar("Beta", "BlendedImage", &beta, 10);
  // cv::imshow("BlendedImage", blendedImage);

  // while (cv::waitKey(100) != 32)
  // {
  //   cv::addWeighted(img, (double)alpha/10.0, img2, (double)beta/10.0, 0.0, blendedImage);
  //   cv::imshow("BlendedImage", blendedImage);
  // }
  // cv::destroyAllWindows();

  /* ========== Basic Linear Transform ========== */
  cv::Mat image, newImage;
  image = cv::imread(argv[1], cv::IMREAD_COLOR);
  
  if (image.empty())
    return EXIT_FAILURE;

  newImage = cv::Mat::zeros(image.size(), image.type());

  int alpha, beta, gamma;
  alpha = 1.0;
  beta  = 0;

  cv::namedWindow("newImage", cv::WINDOW_NORMAL);

  // cv::createTrackbar("Alpha", "newImage", &alpha, 100);
  // cv::createTrackbar("Beta", "newImage", &beta, 1000);
  cv::createTrackbar("Gamma", "newImage", &gamma, 1000);

  cv::imshow("Image", image);
  //cv::imshow("newImage", newImage);

  double t;// = (double)getTickCount();
  while (cv::waitKey(100) != 32)
  {
    // for (int y = 0; y < image.rows; ++y)
    // {
    //   for (int x = 0; x < image.cols; ++x)
    //   {
    //     for (int c = 0; c < image.channels(); ++c)
    //     {
    //       newImage.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>(((double)alpha/10)*image.at<cv::Vec3b>(y,x)[c] + (double)beta/10);
    //     }
    //   }
    // }

    // image.convertTo(newImage, -1, (double)alpha/10, (double)beta/10);

    t = (double)cv::getTickCount();

    // for (int y = 0; y < image.rows; ++y)
    // {
    //   for (int x = 0; x < image.cols; ++x)
    //   {
    //     for (int c = 0; c < image.channels(); ++c)
    //     {
    //       newImage.at<cv::Vec3b>(y,x)[c] = cv::saturate_cast<uchar>(pow(image.at<cv::Vec3b>(y,x)[c] / 255.0, gamma/10.0)*255.0);
    //     }
    //   }
    // }

    cv::Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for( int i = 0; i < 256; ++i)
        p[i] = cv::saturate_cast<uchar>(pow(i / 255.0, gamma/10.0) * 255.0);

    cv::Mat res = image.clone();
    LUT(image, lookUpTable, res);

    t = ((double)cv::getTickCount() - t)/cv::getTickFrequency();
    std::cout << "Times passed in seconds: " << t << std::endl;

    cv::imshow("newImage", res);
  }

  cv::destroyAllWindows();
  return 0;
}