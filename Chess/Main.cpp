#include "Window.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	Window wnd(hInst, pArgs);

	while (wnd.ProcessMessage())
	{
		//enter game loop
	}
	return 0;
}

/* to do:
Create windows procedure
Create keyboard and mouse
Start gfx class
*/