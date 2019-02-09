#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Piece.h"
#include <map>

class Board {
public:
	Board(const std::string spritename, int x, int y);
	~Board() = default;
	Board(const Board& brd) = delete;
	Board operator=(const Board& brd) = delete;
	void DrawBoard(Graphics& gfx);
	int GetCellWidth();
	int GetCellHeight();
	void UpdateBoard(Window& wnd);
	std::map<std::pair<int,int>, std::unique_ptr<Piece>> Pieces;
private:
	int x;
	int y;
	std::pair<int, int> TranslateCoords(Piece* piece);
	Sprite BoardSprite = nullptr;
	static constexpr int cellsPerRow = 8;
	const int cellWidth;
	const int cellHeight;
};