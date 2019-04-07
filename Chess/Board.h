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
	//Constructors/Destructor
	Board(const std::string spritename, int x, int y);
	~Board() = default;
	Board(const Board& brd) = delete;
	Board operator=(const Board& brd) = delete;
	//Standard functions
	void DrawBoard(Graphics& gfx);
	int GetCellWidth();
	int GetCellHeight();
	//Stores the pieces for each colour - Key is a Coord.
	Map whitePieces;
	Map blackPieces;
	//Stores the attacked squares for each colour
	std::set<Coords> whitePieceTargets;
	std::set<Coords> blackPieceTargets;
	//Vector that holds all played moves
	std::vector<std::pair<Coords, Coords>> playedMoves;
	//Helper functions for translating from Coords to screen space and vice versa - public as other classes use to draw
	std::pair<int, int> TranslateCoords(Piece* piece);
	Coords TranslateCoords(int x_in, int y_in);
	std::pair<int, int> TranslateCoords(Coords coords_in);
	//King position functions
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
	Sprite BoardSprite;
	Sprite numbersSprite;
	Sprite lettersSprite;
	
	static constexpr int cellsPerRow = 8;
	const int cellWidth;
	const int cellHeight;
};