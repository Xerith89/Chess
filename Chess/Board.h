#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Piece.h"
#include <map>
#include <algorithm>

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
	std::map<std::pair<int,int>, std::unique_ptr<Piece>> whitePieces;
	std::map<std::pair<int, int>, std::unique_ptr<Piece>> blackPieces;
private:
	Coords selectedPiece;
	Coords selectedTarget;
	Sprite target;
	int x;
	int y;
	std::pair<int, int> TranslateCoords(Piece* piece);
	Coords TranslateCoords(int x_in, int y_in);
	std::pair<int, int> TranslateCoords(Coords coords_in);
	std::vector<Coords> selectedMoves;
	bool pieceSelected = false;
	Sprite BoardSprite = nullptr;
	static constexpr int cellsPerRow = 8;
	const int cellWidth;
	const int cellHeight;
};