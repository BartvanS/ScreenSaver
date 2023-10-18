#include "MainWindow.h"

PCWSTR MainWindow::ClassName() const
{
	return this->className;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    //case WM_CREATE: {

    //}
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

        FillRect(hdc, &ps.rcPaint, brush);
        EndPaint(m_hwnd, &ps);
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}