#pragma once
#include <iostream>
#include <Windows.h>

class KeyboardHook {
public:
	KeyboardHook();

	bool StartHook();

	void StopHook();
	void CheckHook();
	// Public getter method for g_bExitLoop
	bool IsExitLoop() const;

private:
	static LRESULT CALLBACK KeyboardProcStatic(int nCode, WPARAM wParam, LPARAM lParam);

	static HHOOK g_hHook;
	static bool g_bExitLoop;
};