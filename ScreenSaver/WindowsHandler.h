#pragma once
#include <Windows.h>
#include <iostream>

class WindowsHandler
{
private:
	// This function is called whenever a key is pressed
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

public:
	static bool g_bExitLoop; // Global flag to control the loop
	// Global hook handle
	static HHOOK g_hHook;
	void SetHook();
	void UnHook();
};



