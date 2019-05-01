#pragma once
#include "Sprite.h"
#include <array>
#include "Graphics.h"
#include "Window.h"

class Menu {
public:
	Menu();
	void DrawMenuScreen(Graphics& gfx)const;
	void UpdateMenu(Window& wnd);
	int GetSelectedState()const;
private:
	bool newGameState = 0;
	bool joinGameState = 0;
	bool hostGameState = 0;
	bool quitGameState = 0;
	int selectedState;
	Sprite chess;
	std::array<Sprite, 2> newGame = { "./Sprites/Menu/singleplayer1.bmp","./Sprites/Menu/singleplayer2.bmp" };
	std::array<Sprite, 2> hostGame = { "./Sprites/Menu/hostgame1.bmp","./Sprites/Menu/hostgame2.bmp" };
	std::array<Sprite, 2> joinGame = { "./Sprites/Menu/joingame1.bmp","./Sprites/Menu/joingame2.bmp" };
	std::array<Sprite, 2> quitGame = { "./Sprites/Menu/quit1.bmp","./Sprites/Menu/quit2.bmp" };
};

