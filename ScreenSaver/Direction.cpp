#include "Direction.h"
void Direction::Init(int screenWidth, int screenHeight, int stepX, int stepY, POINT startPoint, int objectWidth, int objectHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->stepX = stepX;
	this->stepY = stepY;
	this->objectWidth = objectWidth;
	this->objectHeight = objectHeight;
	this->point = startPoint;
}

POINT Direction::NextPoint()
{
		if (point.x + objectWidth >= (screenWidth - 5))
		{
			stepX *= -1;
		}
		if (point.y + objectHeight >= (screenHeight - 5))
		{
			stepY *= -1;
		}
		if (point.x <= 0)
		{
			stepX = abs(stepX);
		}
		if (point.y <= 0)
		{
			stepY = abs(stepY);
		}
		point.x = point.x + stepX;
		point.y = point.y + stepY;
	return this->point;
}
