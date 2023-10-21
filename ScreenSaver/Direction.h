#pragma once
#include <windows.h>
#include "Mode.h"
class Direction: Mode
{
private:
	int screenWidth;
	int screenHeight;
	int stepX;
	int stepY;
	int objectWidth;
	int objectHeight;
	POINT point;
public:
	void Init(int screenWidth, int screenHeight, int stepX, int stepY, POINT startPoint, int objectWidth = 0, int objectHeight = 0);
	POINT NextPoint();
};

