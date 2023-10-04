#include "Screen.h"
#include <windows.h>

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}
void GetScreenDimension(int* x, int* y) {
	*x = GetSystemMetrics(SM_CXSCREEN);
	*y = GetSystemMetrics(SM_CYSCREEN);
}