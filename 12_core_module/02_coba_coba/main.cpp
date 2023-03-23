#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat img, output, resized;
int threshold1=0, threshold1Max=500, threshold2=0, threshold2Max=500, dilation=0, dilationMax=100;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void on_trackbar(int, void*)
{
  cv::Canny(img, output, threshold1, threshold2);
  static int dilation_type = 0;

  if( dilation_elem == 0 )
    dilation_type = cv::MORPH_RECT;
  else if( dilation_elem == 1 )
    dilation_type = cv::MORPH_CROSS;
  else if( dilation_elem == 2)
    dilation_type = cv::MORPH_ELLIPSE;

  cv::Mat element = getStructuringElement( dilation_type, cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),cv::Point( dilation_size, dilation_size ));

  cv::dilate(output, output, element );
  cv::resize(output, resized, cv::Size(), 0.3, 0.3);
  imshow("Canny", resized);
}

void save_image(std::string &save_path)
{
  static int dilation_type = 0;

  cv::Canny(img, output, threshold1, threshold2);

  if( dilation_elem == 0 )
    dilation_type = cv::MORPH_RECT;
  else if( dilation_elem == 1 )
    dilation_type = cv::MORPH_CROSS;
  else if( dilation_elem == 2)
    dilation_type = cv::MORPH_ELLIPSE;

  cv::Mat element = getStructuringElement(dilation_type, cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ),cv::Point( dilation_size, dilation_size));

  cv::dilate(output, output, element);
  cv::imwrite(save_path, output);

  fprintf(stderr, "Successfully saved in %s", save_path.c_str());
}

int main(int agrc, char *argv[])
{ 
  std::string save_path = argv[1];
  save_path =  save_path + __TIME__ + "_canny.jpg";
  img = cv::imread(argv[1]);
  char key = 0;

  if (img.empty())
    return 1;

  cv::namedWindow("Canny");
  //resized = img.clone();
  //cv::Canny(resized, output, threshold1, threshold2);
  //imshow("Canny", output);

  cv::namedWindow("Canny", cv::WINDOW_NORMAL);
  cv::createTrackbar("CannyThreshold_1", "Canny", &threshold1, threshold1Max, on_trackbar);
  cv::createTrackbar("CannyThreshold_2", "Canny", &threshold2, threshold2Max, on_trackbar);
  cv::createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Canny", &dilation_elem, max_elem, on_trackbar);
  cv::createTrackbar( "Kernel size:\n 2n +1", "Canny", &dilation_size, max_kernel_size, on_trackbar);

  while (key != (char)32)
  {
    key = cv::waitKey(100);
    if (key == 'w')
      save_image(save_path);
  }

  img.release();
  cv::destroyAllWindows();
  return 0;
}
