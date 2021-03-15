// ExamWin32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ExamWin32.h"
#include <windowsx.h>

int g_is_clicked = 0;
int g_x, g_y;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_DESTROY) PostQuitMessage(0);

    else if (uMsg == WM_LBUTTONDOWN) {
        g_is_clicked = 1;

        g_x = GET_X_LPARAM(lParam);
        g_y = GET_Y_LPARAM(lParam);
    }

    else if (uMsg == WM_LBUTTONUP) {
        g_is_clicked = 0;
    }

    else if (uMsg == WM_MOUSEMOVE) {
        if (g_is_clicked == 1) {
            HDC h_dc = GetDC(hWnd);

            //MoveToEx(h_dc, 10, 10, NULL);
            //LineTo(h_dc, 100, 100);

            //int x = lParam & 0x0000FFFF;
            //int y = (lParam >> 16) & 0x0000FFFF;

            //int x = LOWORD(lParam);
            //int y = HIWORD(lParam);

            MoveToEx(h_dc, g_x, g_y, NULL);

            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);

            LineTo(h_dc, x, y);

            g_x = x;
            g_y = y;

            ReleaseDC(hWnd, h_dc);
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;

    wchar_t my_class_name[] = L"tipssoft";
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = my_class_name;
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wc);

    HWND hWnd = CreateWindowW(my_class_name, L"www.tipssoft.com", WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
