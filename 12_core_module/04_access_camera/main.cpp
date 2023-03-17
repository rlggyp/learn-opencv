#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

#define DEVICE_NAME "LogitechBRIO\n"

unsigned char GetCameraID(const char *deviceName)
{
  FILE *fp;
  unsigned char camID = 0;

  if ((fp = popen("v4l2-ctl --list-device | awk '{print $1 $2}'", "r")) != NULL)
  {
    char buff[20];

    while (fgets(buff, sizeof(buff), fp))
    {
      if (strcmp(buff, deviceName) == 0)
      {
        fgets(buff, sizeof(buff), fp);

        for (unsigned char i = 10; i < sizeof(buff) && buff[i] != '\n'; ++i)
        {
          if (buff[i] >= 48 && buff[i] <= 57)
            camID = (buff[i] - '0');
        }
        break;
      }
    }
  }

  pclose(fp);
  return camID;
}

int main(int agrc, char *argv[])
{ 
  cv::VideoCapture cap(GetCameraID(DEVICE_NAME));
  cv::Mat frame;

  bool stopCapture = false;

  while (!stopCapture)
  {
    if ((char)cv::waitKey(50) == (char)32)
      stopCapture = true;

    if (!cap.isOpened())
    {
      if (!cap.open(GetCameraID(DEVICE_NAME)))
      {
        cap.release();
        continue;
      }
    }

    if (cap.read(frame))
      cv::imshow("Frame", frame);
    else
      cap.release();
  }

  cap.release();
  return 0;
}