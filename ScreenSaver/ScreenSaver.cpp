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
// Keyboard hook
HHOOK KeyboardHook::g_hHook = NULL;
bool KeyboardHook::g_bExitLoop = false;
KeyboardHook hook;


static HBITMAP hBitmap = NULL;
static HDC hdcMem = NULL;
int screenWidth;
int screenHeight;
Mouse mouse;
Direction direction;
void Setup() {
	GetScreenDimension(&screenWidth, &screenHeight);
	mouse.Init(screenWidth, screenHeight, 1, 1);
	//if (hBitmap == NULL) {
	//	MessageBox(hwnd, L"Failed to load the bitmap image!", L"Error", MB_ICONERROR);
	//	return -1; // Error
	//}
	hdcMem = CreateCompatibleDC(NULL);
	SelectObject(hdcMem, hBitmap);
	BITMAP bm;
	GetObject(hBitmap, sizeof(BITMAP), &bm);
	direction.Init(screenWidth, screenHeight, 1, 1, bm.bmWidth, bm.bmHeight);
}

int StartProcess() {
	// Move the screensaver untill the key is pressed and IsExitLoop has been triggered
	if (hook.StartHook()) {
		while (hook.IsExitLoop() == false) {
			hook.CheckHook();
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

struct StateInfo
{
	int x = 0;
	int y = 0;
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

int Window(HINSTANCE hInstance, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"Black background class";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	StateInfo* pState = new (std::nothrow) StateInfo;

	if (pState == NULL)
	{
		return -1;
	}
	// get bitmap image size
	BITMAP bm;
	GetObject(hBitmap, sizeof(BITMAP), &bm);
	HWND hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_POPUP,            // Window style

		// Size and position
		0, 0, bm.bmWidth, bm.bmHeight,

		NULL,       // Parent window    
		NULL,       // Menu
		hInstance,  // Instance handle
		pState        // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	

	MSG msg = { };
	//while (GetMessage(&msg, NULL, 0, 0) > 0)
	while (true)
	{
		PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		Sleep(1);
		POINT nextPoint = direction.NextPoint();
		SetWindowPos(hwnd, NULL, nextPoint.x, nextPoint.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	return 0;
}


// WinMain instead of main to run the program as windows application instead of console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	Setup();


	int success = Window(hInstance, nCmdShow);

	// Start the processes. When stopped it returns the exit code
	//return StartProcess();
}



