#include "Window.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	Window wnd(400,300,"Chess");

	while (wnd.ProcessMessage())
	{
		//enter game loop
	}
	return 0;
}

/* to do:
Create keyboard and mouse
Start gfx class
*/