// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Image.h"
#include "KeyboardHook.h"
#include "resource.h"
using namespace std;
// Keyboard hook
HHOOK KeyboardHook::g_hHook = NULL;
bool KeyboardHook::g_bExitLoop = false;
KeyboardHook hook;

int screenWidth;
int screenHeight;
Mouse mouse;
void Setup() {
	GetScreenDimension(&screenWidth, &screenHeight);
	mouse.Init(screenWidth, screenHeight, 1, 1);
	//Image image(screenWidth, screenHeight, 1, 1, "./dvd-image.png");
}

int StartProcess() {
	// Move the screensaver untill the key is pressed and IsExitLoop has been triggered
	if (hook.StartHook()) {
		while (hook.IsExitLoop() == false) {
			hook.CheckHook();
			mouse.Next();
			//image.Next();
			Sleep(1);
		}
	}
	else {
		std::cerr << "Failed to set hook!" << std::endl;
		hook.StopHook();
		return 1;
	}

	hook.StopHook();
	return 0;
}
static HBITMAP hBitmap = NULL;
static HDC hdcMem = NULL;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_CREATE:
		if (hBitmap == NULL) {
			MessageBox(hwnd, L"Failed to load the bitmap image!", L"Error", MB_ICONERROR);
			return -1; // Error
		}
		hdcMem = CreateCompatibleDC(NULL);
		SelectObject(hdcMem, hBitmap);
		break;
	/*case WM_PAINT: {
	
		return 0;
	}*/
	case WM_CLOSE:
		//if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
		if (true) {
			DestroyWindow(hwnd);
			DeleteDC(hdcMem);
			DeleteObject(hBitmap);
			PostQuitMessage(0);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_QUIT: {
		//do nothing
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}




#define WM_LBUTTONDOWN    0x0201
int Window(HINSTANCE hInstance, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"Black background class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// get bitmap image size
	BITMAP bm;
	GetObject(hBitmap, sizeof(BITMAP), &bm);

	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_POPUP,            // Window style

		// Size and position
		0, 0, screenWidth, screenHeight,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		NULL        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);




	// Make screen black
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	// All painting occurs here, between BeginPaint and EndPaint.
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hdc, &ps.rcPaint, brush);

	// Paint bitmap
	BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
	EndPaint(hwnd, &ps);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


// WinMain instead of main to run the program as windows application instead of console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Setup();

	hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	int success = Window(hInstance, nCmdShow);

	// Start the processes. When stopped it returns the exit code
	//return StartProcess();
}



