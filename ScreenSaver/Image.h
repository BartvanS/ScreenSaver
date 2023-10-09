#pragma once
#include "Mode.h"
#include <Windows.h>
#include <string>
using namespace std;
class Image : public Mode
{
private:

	POINT Point;
	string imgPath;
	void SetupImage();
public:
	Image(int screenWidth, int screenHeight, int stepX, int stepY, string imgPath);
	void Next();
};

