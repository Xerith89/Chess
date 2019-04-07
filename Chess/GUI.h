#pragma once
#include "Sprite.h"
#include "Graphics.h"

class GUI {
private:
	Sprite playedMovesSprite;
	Sprite helpPlayerSprite;
	int const playedMovesX = Graphics::GetScreenWidth()-255;
	int const playedMovesY = 10;
	int const helpPlayerX = Graphics::GetScreenWidth() - 215;
	int const helpPlayerY = Graphics::GetScreenHeight()-80;

public:
	GUI();
	void DrawGUI(Graphics& gfx)const;
};