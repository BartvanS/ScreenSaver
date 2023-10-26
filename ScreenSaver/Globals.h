#include <Windows.h>
#include "Screen.h" 
#include "Mouse.h"
#include "Direction.h"
#include "KeyboardHook.h"
#include "resource.h"
#include "Cursor.h"
#include "MainWindow.h"
// Global variables
// Keyboard hook
HHOOK KeyboardHook::g_hHook = NULL;
bool KeyboardHook::g_bExitLoop = false;
KeyboardHook hook;

// Instance of the program
HINSTANCE* phInstance;

// Screen dimensions
int screenWidth;
int screenHeight;

// Mouse and image initialization
Mouse mouse;
Direction image;
MainWindow window;