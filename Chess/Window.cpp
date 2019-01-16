#include "Window.h"
#include <exception>

Window::Window(HINSTANCE hInst, wchar_t * pArgs)
	:
	hInst(hInst),
	args(pArgs)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = wClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	RECT wr;
	wr.left = 200;
	wr.top = 200;
	wr.right = 640;
	wr.bottom = 480;

	HWND hWnd = CreateWindowEx(
		0, wClassName, L"Chess", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right, wr.bottom, nullptr, nullptr, hInst, nullptr
	);
	ShowWindow(hWnd, SW_SHOW);

	if (hWnd == nullptr) { throw L"Could Not Get Window Handle"; }
}

Window::~Window()
{
	UnregisterClass(wClassName, hInst);
}
