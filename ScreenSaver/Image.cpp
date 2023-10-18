#include "Image.h"
#include <windows.h>
#include "resource.h"
int Image::SetupImage(int nCmdShow) {
	//// Create window
	//if (!win.Create(
	//	L"ScreenSaverClass",
	//	L"Learn to Program Windows",
	//	WS_POPUP,
	//	0,
	//	0, 0, screenWidth, screenHeight
	//))
	//{
	//	return -1;
	//}





	//// Load bitmap image into memory
	////hBitmap = LoadBitmap(phInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	////if (hBitmap == NULL) {
	////	MessageBox(hwnd, L"Failed to load the bitmap image!", L"Error", MB_ICONERROR);
	////	return -1; // Error
	////}
	////hdcMem = CreateCompatibleDC(NULL);
	////SelectObject(hdcMem, hBitmap);

	//// Show window
	//ShowWindow(win.Window(), nCmdShow);
	////UpdateWindow(hwnd);

	return 0;
}


Image::~Image()
{
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
}

void Image::Init(int screenWidth, int screenHeight, int stepX, int stepY, HINSTANCE phInstance, int nCmdShow)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->stepX = stepX;
	this->stepY = stepY;
	this->Point.x = 0;
	this->Point.y = 0;
	this->SetupImage(nCmdShow);
}

POINT Image::NextPoint() {
	
	//if (Point.x + this->imgPath.cols >= (screenWidth - 5))
	//{
	//	stepX *= -1;
	//}
	//if (Point.y + this->imgPath.rows >= (screenHeight - 5))
	//{
	//	stepY *= -1;
	//}
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
	POINT newPoint = { Point.x, Point.y };
	return newPoint;
}

//HideConsole();
// Error Handling
//if (imgPath.empty()) {
//	cout << "Image File "
//		<< "Not Found" << endl;

//	// wait for any key press
//	cin.get();
//	return -1;
//}
