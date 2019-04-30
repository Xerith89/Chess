#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Board.h"
#include <algorithm>

class GUI {
private:
	Sprite playedMovesSprite;
	Sprite helpPlayerSprite;
	Sprite promotionSprite;
	Board& brd;
	void TranslateCordToSprite(Coords in);
	const int playedMovesX = Graphics::GetScreenWidth()-255;
	const int playedMovesY = 10;
	const int helpPlayerX = Graphics::GetScreenWidth() - 215;
	const int helpPlayerY = Graphics::GetScreenHeight()-80;
	const int promotionX = (Graphics::GetScreenWidth()/2) - promotionSprite.GetWidth();
	const int promotionY = (Graphics::GetScreenHeight()/2) - promotionSprite.GetHeight();
	//Character sprites
	Sprite to;
	std::vector<Sprite> letters;
	std::vector<Sprite> numbers;
	const int yOffset = 32;
	const int xOffset = 32;
	const int yStart = 100;
public:
	GUI(Board& brd);
	int GetPromoteGraphicX()const;
	int GetPromoteGraphicY()const;
	void DrawGUI(Graphics& gfx)const;
	void DrawPromotion(Graphics& gfx)const;
};