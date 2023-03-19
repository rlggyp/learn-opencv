#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat img, output, resized;
int threshold1=0, threshold1Max=1000, threshold2=0, threshold2Max=1000;

void on_trackbar(int, void*)
{
  cv::Canny(resized, output, threshold1, threshold2);
  imshow("Canny", output);
}

int main(int agrc, char *argv[])
{ 
  std::string save_path = argv[1];
  save_path =  save_path + "_canny.jpg";
  img = cv::imread(argv[1]);
  char key = 0;

  if (img.empty())
    return 1;

  cv::resize(img, resized, cv::Size(), 0.25, 0.25);
  cv::Canny(resized, output, threshold1, threshold2);
  imshow("Canny", output);

  cv::namedWindow("Canny", cv::WINDOW_NORMAL);
  cv::createTrackbar("CannyThreshold_1", "Canny", &threshold1, threshold1Max, on_trackbar);
  cv::createTrackbar("CannyThreshold_2", "Canny", &threshold2, threshold2Max, on_trackbar);

  while (key != (char)32)
  {
    key = cv::waitKey(100);
    if (key == 'w')
    {
      cv::Canny(img, output, threshold1, threshold2);
      cv::imwrite(save_path, output);
      printf("Successfully saved in %s", save_path);
    }
  }

  img.release();
  cv::destroyAllWindows();
  return 0;
}
