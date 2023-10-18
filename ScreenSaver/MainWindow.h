#pragma once
#include "BaseWindow.h"
class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR  ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};