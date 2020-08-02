/*
 *          Copyright 2019, Vitali Baumtrok.
 * Distributed under the Boost Software License, Version 1.0.
 *     (See accompanying file LICENSE or copy at
 *        http://www.boost.org/LICENSE_1_0.txt)
 */

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <gl/GL.h>
#include <gl/GLU.h>

HDC     hDC;				/* device context */
HGLRC   hRC;				/* render context (opengl context) */
HWND    hWnd;				/* window */

LPCWSTR szWindowClass = L"OpenGL";
LPCWSTR szTitle       = L"Example";

WORD width;
WORD height;
WORD prevX;
WORD prevY;
WORD prevWidth;
WORD prevHeight;

void MessageToString(WCHAR *str, size_t strSize, UINT uMsg)
{
	swprintf_s(str, strSize, L"message ");
	switch (uMsg)
	{
	case WM_PRINT: swprintf_s(str + 8, strSize - 8, L"%d (WM_PRINT)\n", (int)(uMsg)); break;
	case WM_PRINTCLIENT: swprintf_s(str + 8, strSize - 8, L"%d (WM_PRINTCLIENT)\n", (int)(uMsg)); break;
	case WM_PAINT: swprintf_s(str + 8, strSize - 8, L"%d (WM_PAINT)\n", (int)(uMsg)); break;
	case WM_SIZE: swprintf_s(str + 8, strSize - 8, L"%d (WM_SIZE)\n", (int)(uMsg)); break;
	case WM_CHAR: swprintf_s(str + 8, strSize - 8, L"%d (WM_CHAR)\n", (int)(uMsg)); break;
	case WM_CLOSE: swprintf_s(str + 8, strSize - 8, L"%d (WM_CLOSE)\n", (int)(uMsg)); break;
	case WM_QUIT: swprintf_s(str + 8, strSize - 8, L"%d (WM_QUIT)\n", (int)(uMsg)); break;
	case WM_DESTROY: swprintf_s(str + 8, strSize - 8, L"%d (WM_DESTROY)\n", (int)(uMsg)); break;
	case WM_MOUSEMOVE: swprintf_s(str + 8, strSize - 8, L"%d (WM_MOUSEMOVE)\n", (int)(uMsg)); break;
	case WM_SETCURSOR: swprintf_s(str + 8, strSize - 8, L"%d (WM_SETCURSOR)\n", (int)(uMsg)); break;
	case WM_NCHITTEST: swprintf_s(str + 8, strSize - 8, L"%d (WM_NCHITTEST)\n", (int)(uMsg)); break;
	case WM_NCMOUSEMOVE: swprintf_s(str + 8, strSize - 8, L"%d (WM_NCMOUSEMOVE)\n", (int)(uMsg)); break;
	case WM_NCMOUSELEAVE: swprintf_s(str + 8, strSize - 8, L"%d (WM_NCMOUSELEAVE)\n", (int)(uMsg)); break;
	default: swprintf_s(str + 8, strSize - 8, L"%d ( )\n", (int)(uMsg)); break;
	}
}

void DrawGraphics()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(0, 1);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2i(-1, -1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(1, -1);
	glEnd();
	glFlush();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR str[40];
	MessageToString(str, 40, message);
	OutputDebugStringW(str);

	switch (message)
	{
	case WM_PAINT:
		PAINTSTRUCT ps;
		DrawGraphics();
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_SYSKEYUP:
		switch (wParam)
		{
		case 121: /* F10 */
			DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
			if (dwStyle & WS_OVERLAPPEDWINDOW)
			{
				RECT rect;
				DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
				MONITORINFO mi = { sizeof(mi) };
				GetWindowRect(hWnd, &rect);
				prevX = rect.left;
				prevY = rect.top;
				prevWidth = rect.right - rect.left;
				prevHeight = rect.bottom - rect.top;

				GetMonitorInfo(MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY), &mi);
				SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(hWnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
				                             mi.rcMonitor.right - mi.rcMonitor.left,
				                             mi.rcMonitor.bottom - mi.rcMonitor.top,
				                             SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
			else
			{
				DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
				MONITORINFO mi = { sizeof(mi) };
				GetMonitorInfo(MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY), &mi);
				SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
				SetWindowPos(hWnd, HWND_NOTOPMOST, prevX, prevY, prevWidth, prevHeight, SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
			}
		}
		break;
	case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case 27: /* ESC key */
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		ReleaseDC(hWnd, hDC);
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC) WndProc; // event handler
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = NULL;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	DWORD  dwStyle;
	int    x = 0;
	int    y = 0;
	int    width = 256;
	int    height = 256;

	dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle, x, y, width, height, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CreateRenderContext()
{
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int                   pixelFormat;

	hDC = GetDC(hWnd);

	/* Initialize bits to 0. */
	memset(&pixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pixelFormatDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescriptor.nVersion = 1;
	pixelFormatDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pixelFormatDescriptor.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescriptor.cColorBits = 32;
	pixelFormat = ChoosePixelFormat(hDC, &pixelFormatDescriptor);

	if (pixelFormat == 0)
	{
		MessageBox(NULL, L"ChoosePixelFormat() failed: Can not find a suitable pixel format.", L"Error", MB_OK);
		return FALSE;
	}
	if (SetPixelFormat(hDC, pixelFormat, &pixelFormatDescriptor) == FALSE)
	{
		MessageBox(NULL, L"SetPixelFormat() failed: Can not set format specified.", L"Error", MB_OK);
		return FALSE;
	}
	DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDescriptor);
	hRC = wglCreateContext(hDC);

	return (hRC != NULL);
}

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_     LPWSTR    lpCmdLine,
                      _In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!MyRegisterClass(hInstance))
	{
		MessageBox(NULL, L"RegisterClass() failed: Cannot create a window.", L"Error", MB_OK);
		return FALSE;
	}

	if (!InitInstance(hInstance, nCmdShow))
	{
		MessageBox(NULL, L"CreateWindow() failed: Can not create a window.", L"Error", MB_OK);
		return FALSE;
	}
	if (!CreateRenderContext())
	{
		MessageBox(NULL, L"wglCreateContext() failed: Can not create an OpenGL context.", L"Error", MB_OK);
		return FALSE;
	}

	wglMakeCurrent(hDC, hRC);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	/* main loop */
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
