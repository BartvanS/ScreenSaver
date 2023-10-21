// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Direction.h"
#include "KeyboardHook.h"
#include "resource.h"
using namespace std;
// Global variables
// Keyboard hook
HHOOK KeyboardHook::g_hHook = NULL;
bool KeyboardHook::g_bExitLoop = false;
KeyboardHook hook;


// Instance of the program
HINSTANCE* phInstance;

// Setup global bitmap
static HBITMAP hBitmap = NULL;
static HDC hdcMem = NULL;
BITMAP bm;
void SetupBitmap() {
	hBitmap = LoadBitmap(*phInstance, MAKEINTRESOURCE(IDB_BITMAP1)); // load bitmap into memory
	hdcMem = CreateCompatibleDC(NULL); // do some memory magic
	SelectObject(hdcMem, hBitmap); // more unknown memory magic
	GetObject(hBitmap, sizeof(BITMAP), &bm); // set the BITMAP bm 
}

int screenWidth;
int screenHeight;
Mouse mouse;
Direction image;
void Setup(HINSTANCE* hinstance) {
	// set the hInstance to the global pointer
	phInstance = hinstance;
	// Set screen dimensions
	GetScreenDimension(&screenWidth, &screenHeight);
	// Set up bitmap
	SetupBitmap();
	// Set up mouse
	mouse.Init(screenWidth, screenHeight, 1, 1);
	//Set up image
	POINT imageStartPoint;
	imageStartPoint.x = 0;
	imageStartPoint.y = 0;
	image.Init(screenWidth, screenHeight, 1, 1, imageStartPoint, bm.bmWidth, bm.bmHeight);
}

struct StateInfo
{
};

inline StateInfo* GetAppState(HWND hwnd)
{
	LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	StateInfo* pState = reinterpret_cast<StateInfo*>(ptr);
	return pState;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	StateInfo* pState;
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
	}
	else
	{
		pState = GetAppState(hwnd);
	}

	switch (uMsg)
	{
	case WM_CREATE:

		break;
	case WM_PAINT: {
		// get bitmap image size
		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);

		// Make screen black
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		//// All painting occurs here, between BeginPaint and EndPaint.
		//HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
		//FillRect(hdc, &ps.rcPaint, brush);

		// Paint bitmap
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);

		break;
	}
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

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

int Window(int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"Black background class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = *phInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	StateInfo* pState = new (std::nothrow) StateInfo;

	if (pState == NULL)
	{
		return -1;
	}
	// Create and show Window
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_POPUP,            // Window style

		// Size and position
		0, 0, bm.bmWidth, bm.bmHeight,

		NULL,       // Parent window    
		NULL,       // Menu
		*phInstance,  // Instance handle
		pState        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);


	// Keep running untill IsExitLoop has been triggered
	MSG msg = { };
	if (hook.StartHook()) {
		while (hook.IsExitLoop() == false) {
			hook.CheckHook();
			// Check if the system has any messages for this window
			if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
				// Translate the message and dispatch it to WindowProc()
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			Sleep(1);
			// Get next point for the image
			POINT nextPoint = image.NextPoint();
			SetWindowPos(hwnd, NULL, nextPoint.x, nextPoint.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			// Move mouse
			mouse.Next();
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


// WinMain instead of main to run the program as windows application instead of console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	Setup(&hInstance);


	return Window( nCmdShow);

}



