#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <iostream>
#include "RPN.h"

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Калькулятор (Lab2)");
TCHAR buf[256];

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			0);
		return 1;
	}
	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		255, 220,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			0);
		return 1;
	}
	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

#define ID_EDIT  99
#define ID_BUTTON    100
#define ID_BUTTON_1  101
#define ID_BUTTON_2  102
#define ID_BUTTON_3  103
#define ID_BUTTON_4  104
#define ID_BUTTON_5  105
#define ID_BUTTON_6  106
#define ID_BUTTON_7  107
#define ID_BUTTON_8  108
#define ID_BUTTON_9  109
#define ID_BUTTON_ADD    110
#define ID_BUTTON_SUB    111
#define ID_BUTTON_MUL    112
#define ID_BUTTON_DIV    113
#define ID_BUTTON_RES   114
#define ID_BUTTON_C    115

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton[17], hEdit, hListBox;
	PAINTSTRUCT ps;
	HDC hdc;
	int i = 0;
	int count = 0, a = 0, b = 0;
	
	switch (message)
	{
	case WM_CREATE:
		hEdit = CreateWindow(_T("edit"), _T("0"), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 10, 5, 230, 35, hWnd, (HMENU)ID_EDIT, hInst, 0);
		hButton[0] = CreateWindow(_T("Button"), _T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 150, 130, 30, hWnd, (HMENU)ID_BUTTON, hInst, 0);
		hButton[1] = CreateWindow(_T("Button"), _T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
		hButton[2] = CreateWindow(_T("Button"), _T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
		hButton[3] = CreateWindow(_T("Button"), _T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
		hButton[4] = CreateWindow(_T("Button"), _T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
		hButton[5] = CreateWindow(_T("Button"), _T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
		hButton[6] = CreateWindow(_T("Button"), _T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
		hButton[7] = CreateWindow(_T("Button"), _T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
		hButton[8] = CreateWindow(_T("Button"), _T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
		hButton[9] = CreateWindow(_T("Button"), _T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
		hButton[10] = CreateWindow(_T("Button"), _T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
		hButton[11] = CreateWindow(_T("Button"), _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
		hButton[12] = CreateWindow(_T("Button"), _T("*"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 115, 43, 30, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
		hButton[13] = CreateWindow(_T("Button"), _T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 115, 43, 30, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
		hButton[14] = CreateWindow(_T("Button"), _T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 150, 90, 30, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
		hButton[15] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 45, 90, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
		break;
	case WM_COMMAND:
		if ((LOWORD(wParam) == ID_BUTTON) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == TEXT('0') && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("0"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == TEXT('0') && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("1"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("2"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("3"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("4"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("5"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("6"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("7"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("8"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			if (*buf == '0' && 0 == buf[1]) *buf = 0;
			StrCat(buf, TEXT("9"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_ADD) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, TEXT("+"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_SUB) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, TEXT("-"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_MUL) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, TEXT("*"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_DIV) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			StrCat(buf, TEXT("/"));
			SetWindowText(hEdit, buf);
		}

		if ((LOWORD(wParam) == ID_BUTTON_RES) && (HIWORD(wParam) == BN_CLICKED))
		{
			GetWindowText(hEdit, buf, sizeof(buf));
			SetWindowText(hEdit, Calculate(buf));
		}

		if ((LOWORD(wParam) == ID_BUTTON_C) && (HIWORD(wParam) == BN_CLICKED))
		{
			SetWindowText(hEdit, TEXT("0"));
			buf[0] = 0;
		}

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}