#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat img, output, resize;
int threshold1=0, threshold1Max=1000, threshold2=0, threshold2Max=1000;

void on_trackbar(int, void*)
{
  cv::Canny(img, output, threshold1, threshold2);
  imshow("Canny", output);
}

int main(int agrc, char *argv[])
{ 
  img = cv::imread(argv[1]);
  char key = 0;

  if (img.empty())
    return 1;

  // imshow("Image", img);

  cv::Canny(img, output, threshold1, threshold2);
  int rows, cols;
  // rows = img.rows/4;
  // cols = img.cols/4;
  // resize = cv::Size(rows, cols);
  
  // imshow("Canny", output);
  cv::namedWindow("Canny1", cv::WINDOW_NORMAL);
  cv::createTrackbar("CannyThreshold_1", "Canny1", &threshold1, threshold1Max, on_trackbar);
  cv::createTrackbar("CannyThreshold_2", "Canny1", &threshold2, threshold2Max, on_trackbar);

  while (key != (char)32)
  {
    key = cv::waitKey(100);
    if (key == 'w')
      cv::imwrite("hasilCanny", output);
  }

  img.release();
  cv::destroyAllWindows();
  return 0;
}
