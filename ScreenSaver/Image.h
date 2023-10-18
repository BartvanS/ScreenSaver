#pragma once
#include "Mode.h"
#include <Windows.h>
#include <string>


using namespace std;
class Image : public Mode
{
private:
	HBITMAP hBitmap = NULL;
	HDC hdcMem = NULL;
	HINSTANCE phInstance;
	POINT Point;
	int SetupImage(int nCmdShow);
public:
	void Init(int screenWidth, int screenHeight, int stepX, int stepY, HINSTANCE phInstance, int nCmdShow);
	~Image();
	POINT NextPoint();
};

