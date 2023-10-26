// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Direction.h"
#include "KeyboardHook.h"
#include "resource.h"
#include "Cursor.h"
#include "MainWindow.h"
#include "Globals.h"
void Setup(HINSTANCE* hinstance) {
	// set the hInstance to the global pointer
	phInstance = hinstance;
	// Set screen dimensions
	GetScreenDimension(&screenWidth, &screenHeight);
	// Set up mouse
	mouse.Init(screenWidth, screenHeight, 1, 1);
	//Set up image
	window.Create(L"Black background class");
	POINT imageStartPoint;
	imageStartPoint.x = 0;
	imageStartPoint.y = 0;
	image.Init(screenWidth, screenHeight, 1, 1, imageStartPoint, 300, 300);
}

void TearDown() {
	// Clean up bitmap
	hook.StopHook();
	// Restore the mouse cursor to normal
	SystemParametersInfo(SPI_SETCURSORS, 0, NULL, SPIF_SENDCHANGE);
}
// WinMain instead of main to run the program as windows application instead of console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Use the _CrtSetDbgFlag function and macros from the crtdbg.h header to enable memory leak checking.  
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
	
	if (enableImage) {
		ShowWindow(window.Window(), nCmdShow);
	}
	if (enableMouse) {
		HICON hCurs = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		if (hCurs != NULL) {
			ChangeCursorForAllSituations(hCurs);
			ShowCursor(true);
			DestroyIcon(hCurs);
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
				SetWindowPos(window.Window(), NULL, nextPoint.x, nextPoint.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
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



