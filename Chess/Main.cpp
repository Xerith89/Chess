#include "Window.h"
#include "Game.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try 
	{
		Window wnd(600, 400, "Chess");
		Game game(wnd);
		wnd.ProcessMessage();
	}
	catch (const std::exception& e) 
	{
		MessageBox(nullptr, "Exception Caught in Main Loop", e.what(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "Exception Caught in Main Loop", "Unknown", MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}
