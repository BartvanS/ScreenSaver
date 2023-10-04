// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "opencv_world470d.lib")
#include <iostream>
#include <windows.h>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
void GetScreenDimension(int* x, int* y);
void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}
void ShowImage() {

}
int main()
{
	//set screen boundaries
	int screenWidth;
	int screenHeight;
	GetScreenDimension(&screenWidth, &screenHeight);
	POINT oldPoint;
	oldPoint.x = 0;
	oldPoint.y = 0;
	//std::cout << screenWidth << "+" << screenHeight;
	int stepX = 3;
	int stepY = 3;
	//HideConsole();
	Mat image = cv::imread("C:\\Users\\bartv\\source\\repos\\ScreenSaver\\ScreenSaver\\dvd-logo.jpeg", IMREAD_COLOR);
	// Error Handling
	if (image.empty()) {
		cout << "Image File "
			<< "Not Found" << endl;

		// wait for any key press
		cin.get();
		return -1;
	}
	cv::imshow("Frame", image);

	while (true) {
		//GetCursorPos(&oldPoint);

		if (oldPoint.x >= (screenWidth -10))
		{
			stepX *= -1;
		}
		if (oldPoint.y >= (screenHeight - 10))
		{
			stepY *= -1;
		}
		if (oldPoint.x == 0)
		{
			stepX = abs(stepX);
		}
		if (oldPoint.y == 0)
		{
			stepY = abs(stepY);
		}
		POINT newPoint;
		newPoint.x = oldPoint.x + stepX;
		newPoint.y = oldPoint.y + stepY;
		oldPoint = newPoint;
		//SetCursorPos(newPoint.x, newPoint.y);
		moveWindow("Frame", newPoint.x, newPoint.y);

		if (pollKey() == 27)
		{
			destroyAllWindows();
			break;
		}
		cout << newPoint.x << endl;
		Sleep(1);


	}
}

void GetScreenDimension(int* x, int* y) {
	*x = GetSystemMetrics(SM_CXSCREEN);
	*y = GetSystemMetrics(SM_CYSCREEN);
}
