#include "MainWindow.h"
HBITMAP MainWindow::hBitmap = NULL; // Initialize hBitmap to NULL
HDC MainWindow::hdcMem = NULL; // Initialize hdcMem to NULL
LRESULT CALLBACK MainWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
	case WM_SETCURSOR: {
		// Prevent the window from changing the cursor to something else
		SetCursor(LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
		break;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

bool MainWindow::Create(const wchar_t CLASS_NAME[])
{
	// Register the window class.
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	// Create and show Window
	hwnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Learn to Program Windows",    // Window text
		WS_POPUP,            // Window style

		// Size and position
		0, 0, 300, 300,
		//0, 0, bm.bmWidth, bm.bmHeight,

		NULL,       // Parent window    
		NULL,       // Menu
		GetModuleHandle(NULL),  // Instance handle
		NULL // Additional application data
	);

	return (hwnd ? TRUE : FALSE);
}
void MainWindow::SetupBitmap() {
	hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1)); // load bitmap into memory
	hdcMem = CreateCompatibleDC(NULL); // do some memory magic
	SelectObject(hdcMem, hBitmap); // more unknown memory magic
	GetObject(hBitmap, sizeof(BITMAP), &bm); // set the BITMAP bm 
}
MainWindow::~MainWindow()
{
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
}

HWND MainWindow::Window() const { return hwnd; }