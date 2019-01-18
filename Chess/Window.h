#pragma once
#include "MyWindows.h"
#include <string>
#include "Mouse.h"

class Window {
private:
	class RegisterWindow {
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		RegisterWindow()noexcept;
		~RegisterWindow();
		RegisterWindow(const RegisterWindow&) = delete;
		RegisterWindow& operator=(const RegisterWindow&) = delete;
		HINSTANCE hInst;
		static constexpr const char* wClassName = "Chess in 3D";
		static RegisterWindow regWin;
	};

public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	Mouse mse;
	bool ProcessMessage();
private:
	LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WINAPI SetupProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WINAPI RedirectProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	int width;
	int height;
	HWND hWnd;
};