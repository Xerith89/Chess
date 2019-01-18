#include "Window.h"
#include <exception>

Window::RegisterWindow Window::RegisterWindow::regWin;

Window::RegisterWindow::RegisterWindow()noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = SetupProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
}

const char * Window::RegisterWindow::GetName()noexcept
{
	return wClassName;
}

HINSTANCE Window::RegisterWindow::GetInstance()noexcept
{
	return regWin.hInst;
}

Window::RegisterWindow::~RegisterWindow()
{
	UnregisterClassA(wClassName, GetInstance());
}


Window::Window(int width, int height, const char* title)
{
	RECT wr;
	wr.left = 200;
	wr.top = 200;
	wr.right = wr.left+width;
	wr.bottom = wr.top+height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false);
	HWND hWnd = CreateWindow(
		RegisterWindow::GetName(), title, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right, wr.bottom, nullptr, nullptr, Window::RegisterWindow::GetInstance(), this
	);
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

bool Window::ProcessMessage()
{
	MSG msg;
	BOOL gResult;
	while (gResult = GetMessage(&msg, nullptr, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return gResult;
	}
	else
	{
		return msg.wParam;
	}
}

LRESULT Window::HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_MOUSEMOVE:
		POINTS pt = MAKEPOINTS(lParam);
		mse.UpdatePos(pt.x, pt.y);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Window::SetupProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW* pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::RedirectProc));
		return pWnd->HandleMessage(hWnd,uMsg,wParam,lParam);
	}
	return DefWindowProc(hWnd,uMsg,wParam, lParam);
}

LRESULT CALLBACK Window::RedirectProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMessage(hWnd, uMsg, wParam, lParam);
}

