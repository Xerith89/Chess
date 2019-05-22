#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Board.h"
#include "imgui/imgui.h"
#include <sstream>
#include <functional>

class GUI {
private:
	Sprite promotionSprite;
	Sprite blackPromotionSprite;
	const int promotionX = (Graphics::GetScreenWidth()/2) - promotionSprite.GetWidth();
	const int promotionY = (Graphics::GetScreenHeight()/2) - promotionSprite.GetHeight();
	char buffer[255];
	Board& brd;
	std::array<char, 8> letters = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'
	};
	std::array<char, 8> numbers = {
		'8', '7', '6', '5', '4', '3', '2', '1'
	};
public:
	GUI(Board& brd);
	void DrawGui(bool multiplayer);
	void GetAddress();
	std::string GetBuffer();
	int GetPromoteGraphicX()const;
	int GetPromoteGraphicY()const;
	void DrawPromotionBlack(Graphics& gfx)const;
	void DrawPromotion(Graphics& gfx)const;
};