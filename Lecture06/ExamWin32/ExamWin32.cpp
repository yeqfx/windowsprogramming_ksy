﻿// ExamWin32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ExamWin32.h"
#include <windowsx.h>

int g_is_clicked = 0;
RECT g_rect = { 10, 10, 50, 50 };
POINT g_prev_pos;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_DESTROY) PostQuitMessage(0);

    else if (uMsg == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC h_dc = BeginPaint(hWnd, &ps);

        Rectangle(h_dc, g_rect.left, g_rect.top, g_rect.right, g_rect.bottom);

        EndPaint(hWnd, &ps);
    }

    else if (uMsg == WM_LBUTTONDOWN) {
        g_prev_pos = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

        if (PtInRect(&g_rect, g_prev_pos)) {
            g_is_clicked = 1;
            SetCapture(hWnd);
        }

        //int x = GET_X_LPARAM(lParam);
        //int y = GET_Y_LPARAM(lParam);
        //if (x >= g_rect.left && x <= g_rect.right && y >= g_rect.top && y <= g_rect.bottom) {
        //    g_is_clicked = 1;
        //}
    }

    else if (uMsg == WM_LBUTTONUP) {
        g_is_clicked = 0;
        ReleaseCapture();
    }

    else if (uMsg == WM_MOUSEMOVE) {
        if (g_is_clicked == 1) {
            //HDC h_dc = GetDC(hWnd);
            
            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);

            OffsetRect(&g_rect, x - g_prev_pos.x, y - g_prev_pos.y);

            //int h_interval = x - g_prev_pos.x;
            //int v_interval = y - g_prev_pos.y;

            //g_rect.left += h_interval;
            //g_rect.right += h_interval;
            //g_rect.top += v_interval;
            //g_rect.bottom += v_interval;

            //Rectangle(h_dc, g_rect.left, g_rect.top, g_rect.right, g_rect.bottom);
            InvalidateRect(hWnd, NULL, TRUE);

            g_prev_pos.x = x;
            g_prev_pos.y = y;

            //ReleaseDC(hWnd, h_dc);
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
