#pragma once
#include "MyWindows.h"
#include <string>

class Window {

public:
	Window(HINSTANCE hInst, wchar_t* pArgs);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
private:
	const wchar_t* wClassName = L"Chess in 3D";
	std::wstring args;
	HINSTANCE hInst = nullptr;
};