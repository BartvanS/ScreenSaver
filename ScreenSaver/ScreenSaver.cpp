// ScreenSaver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Image.h"
using namespace std;
// Global hook handle
HHOOK g_hHook = NULL;
bool g_bExitLoop = false; // Global flag to control the loop
// This function is called whenever a key is pressed
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;

            // Check if the key combination you want to hook is pressed
            if (pKeyStruct->vkCode == VK_F1 && GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                // Your code to handle the keybind goes here
                std::cout << "F1 + Ctrl was pressed!" << std::endl;
                g_bExitLoop = true;
            }
        }
    }

    // Call the next hook in the hook chain
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

int main()
{
    g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (g_hHook == NULL) {
        std::cerr << "Failed to set hook!" << std::endl;
        return 1;
    }

    // Message loop
    MSG msg;
    while (g_bExitLoop == false) {
        if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        int screenWidth;
        int screenHeight;
        GetScreenDimension(&screenWidth, &screenHeight);
        Mouse mouse(screenWidth, screenHeight, 1, 1);
        Image image(screenWidth, screenHeight, 1, 1, "./dvd-image.png");

        mouse.Next();
        image.Next();
        Sleep(1);
    }

    // Unhook and exit
    UnhookWindowsHookEx(g_hHook);
    return 0;

}
 


