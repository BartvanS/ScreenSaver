// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma comment(lib, "opencv_world470d.lib")
#include <iostream>
#include <windows.h>
#include <opencv2\opencv.hpp>
#include "Screen.h" 
#include "Mouse.h"
using namespace std;
using namespace cv;


int main()
{
	//set screen boundaries
	int screenWidth;
	int screenHeight;
	GetScreenDimension(&screenWidth, &screenHeight);
	Mouse mouse(screenWidth, screenHeight, 1, 1);
	while (true)
	{
		mouse.Next();
		Sleep(1);
	}
	//Mouse mouse = new Mouse("C:\\Users\\bartv\\source\\repos\\ScreenSaver\\ScreenSaver\\dvd-logo.jpeg", screenWidth, screenHeight);
		//moveWindow("Frame", newPoint.x, newPoint.y);

	//if (pollKey() == 27)
	//{
	//	destroyAllWindows();
	//	break;
	//}
	//cout << newPoint.x << endl;
	//Sleep(1);



}


