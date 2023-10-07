#pragma once
#include <opencv2\opencv.hpp>
#include "Mode.h"
#include <Windows.h>
using namespace cv;
using namespace std;
class Image : public Mode
{
private:

	POINT Point;
	Mat image;
	void SetupImage();
public:
	Image(int screenWidth, int screenHeight, int stepX, int stepY, string imgPath);
	void Next();
};

