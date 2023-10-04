// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "opencv_world470d.lib")
#include <iostream>
#include <windows.h>
#include <opencv2\opencv.hpp>
#include "Screen.h" 
#include "Mouse.h"
#include "Image.h"
using namespace std;
using namespace cv;


int main()
{
	//set screen boundaries
	int screenWidth;
	int screenHeight;
	GetScreenDimension(&screenWidth, &screenHeight);
	Mouse mouse(screenWidth, screenHeight, 1, 1);
	Image image(screenWidth, screenHeight, 1, 1, "C:\\Users\\bartv\\source\\repos\\ScreenSaver\\ScreenSaver\\dvd-logo.jpeg");
	while (true)
	{
		// When escape key is pressed, escape while loop
		if (pollKey() == 27)
		{
			destroyAllWindows();
			break;
		}
		mouse.Next();
		image.Next();
		Sleep(1);
	}
}


