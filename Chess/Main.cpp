#include "Window.h"
#include "Game.h"
#include "imgui_manager.h"
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try 
	{
		imgui_manager imMan;
		Window wnd(800, 600, "Chess");
		Game game(wnd);
		while (wnd.ProcessMessage())
		{
			game.Run();
		}
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
