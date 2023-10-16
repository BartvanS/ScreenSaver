#pragma once
#include <windows.h>
#include "Mode.h"
class Mouse : public Mode
{
private:
	POINT GetMousePosition();

public:
	Mouse();
	Mouse(int screenWidth, int screenHeight, int stepX, int stepY);

	int Init(int screenWidth, int screenHeight, int stepX, int stepY);


	void Next();

};

