#include <string>
#include <stdio.h>
#include <unistd.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>

void RemoveSpace(std::string *deviceName, unsigned char *totalWord)
{
  char temp[50];

  strcpy(temp, deviceName->c_str());
  *deviceName = temp[0];

  for (unsigned char i = 1; i < sizeof(temp); ++i)
  {
    if (temp[i] == 32)
      ++*totalWord;
    else
    {
      if (temp[i] == '\0')
        break;
      else
        *deviceName += temp[i];
    }
  }
  *deviceName += '\n';
}

void GetCommand(std::string *command, unsigned char *totalWord)
{
  char temp[10];
  *command = "v4l2-ctl --list-device | awk '{print";

  for (unsigned char i = 1; i <= *totalWord; ++i)
  {
    if (i != *totalWord)
      sprintf(temp, " $%d", i);
    else
      sprintf(temp, " $%d}'", i);

    *command += temp;
  }
}

unsigned char GetCameraID(std::string *deviceName)
{
  static FILE *fp;
  static std::string command;
  static unsigned char camID;
  static bool init = true;

  if (init)
  {
    unsigned char totalWord = 1;

    init = false;
    RemoveSpace(deviceName, &totalWord);
    GetCommand(&command, &totalWord);
  }

  camID = 0;

  if ((fp = popen(command.c_str(), "r")) != NULL)
  {
    char buff[50];

    while (fgets(buff, sizeof(buff), fp))
    {
      if (strcmp(buff, deviceName->c_str()) == 0)
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

int main(int argc, char *argv[])
{ 
  std::string deviceName  = argv[1];

  for (char i = 2; i < argc; ++i)
    deviceName += " " + std::string(argv[i]);
  
  cv::VideoCapture cap(GetCameraID(&deviceName));
  cv::Mat frame;

  char key;
  bool stopCapture = false;

  while (!stopCapture)
  {
    key = cv::waitKey(50);

    if (key == (char)32)
      stopCapture = true;

    if (key == (char)'r')
    {
      cap.release();
      if (!cap.open(GetCameraID(&deviceName)))
      {
        cap.release();
        continue;
      }
    }

    if (!cap.isOpened())
    {
      if (!cap.open(GetCameraID(&deviceName)))
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