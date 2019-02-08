#pragma once
#include "Sprite.h"

class Board {
public:
	Board(const std::string spritename);
	~Board() = default;
	Board(const Board& brd) = delete;
	Board operator=(const Board& brd) = delete;
	void DrawBoard(int x, int y)const;
private:
	Sprite BoardSprite = nullptr;
};