#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int x, int y, const std::string spritename,bool white, Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
	virtual void GetTargets(Map* oppoPieces)override;
	virtual int GetScore()override;
	virtual int GetBetterScore()override;
private:
	const int score = 900;
	std::array<int, 64> const boardPositionValue = {
		-20, -10, -10, -5, -5, -10, -10, -20,
		-10,   0,   0,  0,  0,   0,   0, -10,
		-10,   5,   5,  5,  5,   5,   0, -10,
		  0,   0,   5,  5,  5,   5,   0, -5,
		 -5,   0,   5,  5,  5,   5,   0, -5,
		-10,   0,   5,  5,  5,   5,   0, -10,
		-10,   0,   5,  0,  0,   0,   0, -10,
		-20, -10, -10, -5, -5, -10, -10, -20 
	};
};