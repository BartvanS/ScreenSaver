#include "Cursor.h"
void ChangeCursorForAllSituations(HCURSOR hCursor) {
    // For some reason the definitions of these cursors are not in the windows.h file so the codes are taken from https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setsystemcursor#parameters
    SetSystemCursor(hCursor, 32512);
    SetSystemCursor(hCursor, 32513);
    SetSystemCursor(hCursor, 32514);
    SetSystemCursor(hCursor, 32515);
    SetSystemCursor(hCursor, 32516);
    SetSystemCursor(hCursor, 32642);
    SetSystemCursor(hCursor, 32643);
    SetSystemCursor(hCursor, 32644);
    SetSystemCursor(hCursor, 32645);
    SetSystemCursor(hCursor, 32646);
    SetSystemCursor(hCursor, 32648);
    SetSystemCursor(hCursor, 32649);
    SetSystemCursor(hCursor, 32650);

    /*SetSystemCursor(hCursor, OCR_NORMAL);
    SetSystemCursor(hCursor, OCR_IBEAM);
    SetSystemCursor(hCursor, OCR_WAIT);
    SetSystemCursor(hCursor, OCR_CROSS);
    SetSystemCursor(hCursor, OCR_UP);
    SetSystemCursor(hCursor, OCR_SIZE);
    SetSystemCursor(hCursor, OCR_ICON);
    SetSystemCursor(hCursor, OCR_SIZENWSE);
    SetSystemCursor(hCursor, OCR_SIZENESW);
    SetSystemCursor(hCursor, OCR_SIZEWE);
    SetSystemCursor(hCursor, OCR_SIZENS);
    SetSystemCursor(hCursor, OCR_SIZEALL);
    SetSystemCursor(hCursor, OCR_NO);
    SetSystemCursor(hCursor, OCR_HAND);
    SetSystemCursor(hCursor, OCR_APPSTARTING);
    SetSystemCursor(hCursor, OCR_HELP);*/
}
