#include "Menu.h"

Menu::Menu()
	:
	chess("./Sprites/Menu/chess.bmp")
{
}

void Menu::DrawMenuScreen(Graphics& gfx) const
{
	gfx.DrawSprite(180, 5, chess);
	gfx.DrawSprite(320, 150, newGame.at(newGameState));
	gfx.DrawSprite(320, 200, hostGame.at(hostGameState));
	gfx.DrawSprite(320, 250, joinGame.at(joinGameState));
	gfx.DrawSprite(320, 300, quitGame.at(quitGameState));
}

void Menu::UpdateMenu(Window& wnd)
{
	//Check in bounds of new game sprite
	if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + newGame.at(newGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 150 && wnd.inpt.GetMseY() < 150 + newGame.at(newGameState).GetHeight())
	{
		newGameState = 1;
		selectedState = 1;
		joinGameState = 0;
		quitGameState = 0;
		hostGameState = 0;
	}
	
	//Host sprite bounds
	else if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + hostGame.at(hostGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 200 && wnd.inpt.GetMseY() < 200 + hostGame.at(hostGameState).GetHeight())
	{
		newGameState = 0;
		joinGameState = 0;
		quitGameState = 0;
		hostGameState = 1;
		selectedState = 2;
	}
	
	//Join sprite bounds
	else if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + joinGame.at(joinGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 250 && wnd.inpt.GetMseY() < 250 + joinGame.at(joinGameState).GetHeight())
	{
		joinGameState = 1;
		selectedState = 3;
		newGameState = 0;
		quitGameState = 0;
		hostGameState = 0;
	}

	//Join sprite bounds
	else if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + quitGame.at(quitGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 300 && wnd.inpt.GetMseY() < 300 + quitGame.at(quitGameState).GetHeight())
	{
		quitGameState = 1;
		selectedState = 4;
		newGameState = 0;
		joinGameState = 0;
		hostGameState = 0;
	}
	else
	{
		quitGameState = 0;
		selectedState = 0;
	}
}

int Menu::GetSelectedState() const
{
	return selectedState;
}
