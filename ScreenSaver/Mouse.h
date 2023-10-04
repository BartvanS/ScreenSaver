#pragma once
#include <windows.h>

class Mouse
{
private:
	int screenWidth;
	int screenHeight;
	int stepX;
	int stepY;
	//char* imPath;
	POINT GetMousePosition();

public:
	Mouse(int screenWidth, int screenHeight, int stepX, int stepY);


	void Next();

};

