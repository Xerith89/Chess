#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Board.h"
#include "imgui/imgui.h"

class GUI {
private:
	Sprite promotionSprite;
	Sprite blackPromotionSprite;
	const int promotionX = (Graphics::GetScreenWidth()/2) - promotionSprite.GetWidth();
	const int promotionY = (Graphics::GetScreenHeight()/2) - promotionSprite.GetHeight();
	char buffer[255];
public:
	GUI();
	void DrawMoves();
	void DrawHint();
	void GetAddress();
	std::string GetBuffer();
	int GetPromoteGraphicX()const;
	int GetPromoteGraphicY()const;
	void DrawPromotionBlack(Graphics& gfx)const;
	void DrawPromotion(Graphics& gfx)const;
};