// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Image.h"
#include "KeyboardHook.h"
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
void OnSize(HWND hwnd, UINT flag, int width, int height)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // All painting occurs here, between BeginPaint and EndPaint.
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &ps.rcPaint, brush);

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_SIZE:
    {
        int width = LOWORD(lParam);  // Macro to get the low-order word.
        int height = HIWORD(lParam); // Macro to get the high-order word.

        // Respond to the message:
        OnSize(hwnd, (UINT)wParam, width, height);
        return 0;
    }
    case WM_CLOSE:
        if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        // Else: User canceled. Do nothing.
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_QUIT: {
        //do nothing
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}




#define WM_LBUTTONDOWN    0x0201
int Window(HINSTANCE hInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Black background class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

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
    int success = Window(hInstance, nCmdShow);

    Setup();
    // Start the processes. When stopped it returns the exit code
    return StartProcess();
}
 


