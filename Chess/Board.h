#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "Piece.h"
#include <map>
#include <algorithm>
#include <set>

class Board {
	using Map = std::map<std::pair<int, int>, std::shared_ptr<Piece>>;
public:
	Board(const std::string spritename, int x, int y);
	~Board() = default;
	Board(const Board& brd) = delete;
	Board operator=(const Board& brd) = delete;
	void DrawBoard(Graphics& gfx);
	int GetCellWidth();
	int GetCellHeight();
	Map whitePieces;
	Map blackPieces;
	std::set<Coords> whitePieceTargets;
	std::set<Coords> blackPieceTargets;
	std::pair<int, int> TranslateCoords(Piece* piece);
	Coords TranslateCoords(int x_in, int y_in);
	std::pair<int, int> TranslateCoords(Coords coords_in);
	void UpdateWhiteKingLoc(Coords new_loc);
	Coords GetWhiteKingLoc()const;
	void UpdateBlackKingLoc(Coords new_loc);
	Coords GetBlackKingLoc()const;
	bool CheckValidMove(const Coords from, const Coords to,const bool whitePiece);
private:
	Coords whiteKingLoc = { 4,7 };
	Coords blackKingLoc = { 4,0 };
	int x;
	int y;
	Sprite BoardSprite = nullptr;
	static constexpr int cellsPerRow = 8;
	const int cellWidth;
	const int cellHeight;
};