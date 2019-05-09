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
	gfx.DrawSprite(320, 230, hostGame.at(hostGameState));
	gfx.DrawSprite(320, 310, joinGame.at(joinGameState));
	gfx.DrawSprite(320, 390, quitGame.at(quitGameState));
}

void Menu::UpdateMenu(Window& wnd, irrklang::ISoundEngine* engine)
{
	//Check in bounds of new game sprite
	if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + newGame.at(newGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 150 && wnd.inpt.GetMseY() < 150 + newGame.at(newGameState).GetHeight())
	{
		if (playSound)
		{
			engine->play2D("./Sounds/click.wav", false);
			playSound = false;
		}
		newGameState = 1;
		selectedState = 1;
		joinGameState = 0;
		quitGameState = 0;
		hostGameState = 0;
	}
	
	//Host sprite bounds
	else if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + hostGame.at(hostGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 230 && wnd.inpt.GetMseY() < 230 + hostGame.at(hostGameState).GetHeight())
	{
		if (playSound)
		{
			engine->play2D("./Sounds/click.wav", false);
			playSound = false;
		}
		newGameState = 0;
		joinGameState = 0;
		quitGameState = 0;
		hostGameState = 1;
		selectedState = 2;
	}
	
	//Join sprite bounds
	else if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + joinGame.at(joinGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 310 && wnd.inpt.GetMseY() < 310 + joinGame.at(joinGameState).GetHeight())
	{
		if (playSound)
		{
			engine->play2D("./Sounds/click.wav", false);
			playSound = false;
		}
		joinGameState = 1;
		selectedState = 3;
		newGameState = 0;
		quitGameState = 0;
		hostGameState = 0;
	}

	//Join sprite bounds
	else if (wnd.inpt.GetMseX() > 320 && wnd.inpt.GetMseX() < 320 + quitGame.at(quitGameState).GetWidth() &&
		wnd.inpt.GetMseY() > 390 && wnd.inpt.GetMseY() < 390 + quitGame.at(quitGameState).GetHeight())
	{
		if (playSound)
		{
			engine->play2D("./Sounds/click.wav", false);
			playSound = false;
		}
		quitGameState = 1;
		selectedState = 4;
		newGameState = 0;
		joinGameState = 0;
		hostGameState = 0;
	}
	else
	{
		playSound = true;
		quitGameState = 0;
		selectedState = 0;
		newGameState = 0;
		joinGameState = 0;
		hostGameState = 0;
	}
}

int Menu::GetSelectedState() const
{
	return selectedState;
}
