#pragma once
#include <Windows.h>
#include "resource.h"
class MainWindow
{
private:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND hwnd;
	static HBITMAP hBitmap;
	static HDC hdcMem;
	BITMAP bm;
public:
	MainWindow() {
		SetupBitmap();	
	}
	void SetupBitmap();
	bool Create(const wchar_t CLASS_NAME[]);
	HWND Window() const;
	~MainWindow();
};


