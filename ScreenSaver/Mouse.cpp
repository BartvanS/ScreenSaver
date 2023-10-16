#include "Mouse.h"
#include <windows.h>
using namespace std;

Mouse::Mouse() {

}

Mouse::Mouse(int screenWidth, int screenHeight, int stepX, int stepY)
{
	this->Init(screenWidth, screenHeight, stepX, stepY);
}

int Mouse::Init(int screenWidth, int screenHeight, int stepX, int stepY) {
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->stepX = stepX;
	this->stepY = stepY;
	return 1;
}

POINT Mouse::GetMousePosition() {
	POINT Point;
	Point.x = 0;
	Point.y = 0;
	GetCursorPos(&Point);
	return Point;
}

void Mouse::Next() {
	POINT Point = this->GetMousePosition();
	if (Point.x >= (screenWidth - 5))
	{
		stepX *= -1;
	}
	if (Point.y >= (screenHeight - 5))
	{
		stepY *= -1;
	}
	if (Point.x <= 0)
	{
		stepX = abs(stepX);
	}
	if (Point.y <= 0)
	{
		stepY = abs(stepY);
	}
	Point.x = Point.x + stepX;
	Point.y = Point.y + stepY;
	SetCursorPos(Point.x, Point.y);
}
