// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Direction.h"
#include "KeyboardHook.h"
#include "resource.h"
#include "Cursor.h"
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

// Screen dimensions
int screenWidth;
int screenHeight;
// Mouse and image initialization
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

void TearDown() {
	// Clean up bitmap
	hook.StopHook();
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
	// Restore the mouse cursor to normal
	SystemParametersInfo(SPI_SETCURSORS, 0, NULL, SPIF_SENDCHANGE);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_PAINT: {
		// get bitmap image size
		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);

		// Make screen black
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// Paint bitmap
		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);

		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

// Creates a window with its corresponding class and returns the handle to the window
HWND Window(int nCmdShow) {
	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Black background class";
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = *phInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

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
		NULL // Additional application data
	);

	if (hwnd == NULL)
	{
		return 0;
	}
	return hwnd;
}

#include <iostream>
#include <string>
#include <vector>

std::vector<std::wstring> ExtractWordsFromCmdLine(LPSTR lpCmdLine) {
	std::vector<std::wstring> words;
	std::wstring currentWord;
	bool inWord = false;
	for (int i = 0; lpCmdLine[i] != L'\0'; i++) {
		if (lpCmdLine[i] == L' ' || lpCmdLine[i] == L'\t') {
			if (inWord) {
				words.push_back(currentWord);
				currentWord.clear();
				inWord = false;
			}
		}
		else {
			currentWord += lpCmdLine[i];
			inWord = true;
		}
	}
	if (inWord) {
		words.push_back(currentWord);
	}
	return words;
}

// WinMain instead of main to run the program as windows application instead of console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Setup(&hInstance);
	int exitMessage = 0;
	bool enableMouse = true;
	bool enableImage = true;
	if (lpCmdLine[0] == L'm')
	{
		enableImage = false;
	}
	if (lpCmdLine[0] == L'i')
	{
		enableMouse = false;
	}
	//create window
	HWND hwnd = Window(nCmdShow);
	if (enableImage) {
		ShowWindow(hwnd, nCmdShow);
	}
	if (enableMouse) {
		HICON hCurs = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		if (hCurs != NULL) {
			ChangeCursorForAllSituations(hCurs);
			ShowCursor(true);
		}
		else {
			return -1;
		}
	}
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
			if (enableImage)
			{
				POINT nextPoint = image.NextPoint();
				SetWindowPos(hwnd, NULL, nextPoint.x, nextPoint.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
			}
			// Move mouse
			if (enableMouse)
			{
				mouse.Next();
			}
		}
	}
	else {
		std::cerr << "Failed to set hook!" << std::endl;
		exitMessage = -1;
	}

	TearDown();
	return exitMessage;
}



