#pragma once
#include "Sprite.h"
#include <array>
#include "Graphics.h"
#include "Window.h"
#include "ik/irrKlang.h"

class Menu {
public:
	Menu();
	void DrawMenuScreen(Graphics& gfx)const;
	void UpdateMenu(Window& wnd, irrklang::ISoundEngine* engine);
	int GetSelectedState()const;
private:
	bool newGameState = 0;
	bool joinGameState = 0;
	bool hostGameState = 0;
	bool quitGameState = 0;
	bool playSound = 1;
	int selectedState;
	Sprite chess;
	std::array<Sprite, 2> newGame = { Sprite("./Sprites/Menu/singleplayer1.bmp"), Sprite("./Sprites/Menu/singleplayer2.bmp") };
	std::array<Sprite, 2> hostGame = { Sprite("./Sprites/Menu/hostgame1.bmp"), Sprite("./Sprites/Menu/hostgame2.bmp") };
	std::array<Sprite, 2> joinGame = { Sprite("./Sprites/Menu/joingame1.bmp"),Sprite("./Sprites/Menu/joingame2.bmp") };
	std::array<Sprite, 2> quitGame = { Sprite("./Sprites/Menu/quit1.bmp"),Sprite("./Sprites/Menu/quit2.bmp") };
};

