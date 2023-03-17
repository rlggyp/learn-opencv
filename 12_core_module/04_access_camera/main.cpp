#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

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
  unsigned char camID = GetCameraID("V380FHD\n");
  cv::VideoCapture cap(camID);
  cv::Mat frame;

  bool stopCapture = false;

  while (!stopCapture)
  {
    if (!cap.isOpened())
    {
      if (!cap.open(GetCameraID("V380FHD\n")))
      {
        cap.release();
        continue;
      }
    }

    if (cap.read(frame))
      cv::imshow("Frame", frame);
    else
      cap.release();

    if ((char)cv::waitKey(50) == (char)32)
      stopCapture = true;
  }
  cap.release();
  return 0;
}