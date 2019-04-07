#pragma once
#include "Sprite.h"
#include "Graphics.h"

class GUI {
private:
	Sprite playedMovesSprite;
	Sprite helpPlayerSprite;
	Sprite promotionSprite;
	int const playedMovesX = Graphics::GetScreenWidth()-255;
	int const playedMovesY = 10;
	int const helpPlayerX = Graphics::GetScreenWidth() - 215;
	int const helpPlayerY = Graphics::GetScreenHeight()-80;
	int const promotionX = (Graphics::GetScreenWidth()/2) - promotionSprite.GetWidth();
	int const promotionY = (Graphics::GetScreenHeight()/2) - promotionSprite.GetHeight();

public:
	GUI();
	int GetPromoteGraphicX()const;
	int GetPromoteGraphicY()const;
	void DrawGUI(Graphics& gfx)const;
	void DrawPromotion(Graphics& gfx)const;
};