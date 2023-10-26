#include "KeyboardHook.h"

 KeyboardHook::KeyboardHook() {
	g_hHook = NULL;
	g_bExitLoop = false;
}

 bool KeyboardHook::StartHook() {
	 g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProcStatic, NULL, 0);
	 return g_hHook != NULL;
 }

 void KeyboardHook::StopHook() {
	 if (g_hHook != NULL) {
		 UnhookWindowsHookEx(g_hHook);
		 g_hHook = NULL;
	 }
 }

 void KeyboardHook::CheckHook() {
	 MSG msg;
	 if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		 TranslateMessage(&msg);
		 DispatchMessage(&msg);
	 }
 }

 // Public getter method for g_bExitLoop
 bool KeyboardHook::IsExitLoop() const {
	 return g_bExitLoop;
 }

 LRESULT KeyboardHook::KeyboardProcStatic(int nCode, WPARAM wParam, LPARAM lParam) {
	 // You can access class members or call other class methods here if needed
	 if (nCode >= 0) {
		 if (wParam == WM_KEYDOWN) {
			 KBDLLHOOKSTRUCT* pKeyStruct = (KBDLLHOOKSTRUCT*)lParam;

			 // Check if the key combination you want to hook is pressed
				 if (pKeyStruct->vkCode == VK_ESCAPE) {
				 // Set the flag to exit the loop
				 g_bExitLoop = true;
			 }
		 }
	 }

	 // Call the next hook in the hook chain
	 return CallNextHookEx(g_hHook, nCode, wParam, lParam);
 }
