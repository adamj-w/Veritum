#include <Veritum.h>

#include "Win32Window.h"
#include <atlbase.h>

LPCTSTR toTstr(const char* str)
{
	USES_CONVERSION;
	return A2CT(str);
}

namespace vrtm {

static LPCTSTR _windowClassName = "veritum";

#ifndef GWL_USERDATA
#define GWL_USERDATA -21
#endif

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Win32Window* winClass = (Win32Window*)GetWindowLongPtr(hWnd, GWL_USERDATA);

	if (msg == WM_CREATE) {
		LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
		SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)createStruct->lpCreateParams);
		return 0;
	}

	if(winClass)
		return winClass->_wndProc(hWnd, msg, wParam, lParam);

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Win32Window::_wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		destroy();
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Win32Window::create(const char* title, uint32_t width, uint32_t height)
{
	hInst = GetModuleHandle(NULL);

	WNDCLASSEX wcex = {};
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = _windowClassName;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInst;
	wcex.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(hInst, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	if (!RegisterClassEx(&wcex)) throw std::runtime_error("Failed to register window class");

	DWORD wStyle = WS_OVERLAPPEDWINDOW ^ (WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT winRect = { 0, 0, (LONG)width, (LONG)height };
	AdjustWindowRect(&winRect, wStyle, FALSE);
	int winLeft = screenWidth / 2 - width / 2;
	int winTop = screenHeight / 2 - height / 2;

	hWnd = CreateWindow(_windowClassName, toTstr(title), wStyle,
		winLeft, winTop, width, height, NULL, NULL, hInst, this);
	if (!hWnd) throw std::runtime_error("Failed to create window");

	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
}

void Win32Window::destroy()
{
	DestroyWindow(hWnd);
}

void Win32Window::pollEvents()
{
	MSG msg;
	while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Win32Window::setTitle(const char* title)
{
	SetWindowText(hWnd, toTstr(title));
}

glm::uvec2 Win32Window::getDimensions()
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	return glm::uvec2(rect.right - rect.left, rect.bottom - rect.top);
}

void Win32Window::setDimensions(glm::uvec2 dim)
{
	RECT rect;
	GetWindowRect(hWnd, &rect);
	rect.right = rect.left + dim.x;
	rect.bottom = rect.top + dim.y;
	GetWindowRect(hWnd, &rect);
}

}
