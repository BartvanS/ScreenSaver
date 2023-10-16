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

HHOOK KeyboardHook::g_hHook = NULL;
bool KeyboardHook::g_bExitLoop = false;
// WinMain instead of main to run the program as windows application instead of console application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    Setup();

    // Start the processes. When stopped it returns the exit code
    return StartProcess();
}
 


