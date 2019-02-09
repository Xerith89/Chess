#pragma once
#include "Sprite.h"
#include "Graphics.h"

class Board {
public:
	Board(const std::string spritename);
	~Board() = default;
	Board(const Board& brd) = delete;
	Board operator=(const Board& brd) = delete;
	void DrawBoard(int x, int y, Graphics& gfx)const;
private:
	Sprite BoardSprite = nullptr;
};