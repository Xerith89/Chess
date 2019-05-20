#pragma once
#include "Piece.h"

class Rook : public Piece {
public:
	Rook(int x, int y, const std::string spritename, bool white,Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
	virtual void GetTargets(Map* oppoPieces)override;
	virtual int GetScore()override;
	virtual int GetBetterScore()override;
private:
	const int score = 500;
	std::array<int, 64> const boardPositionValue = {
		  0,  0,  0,  5,  5,  0,  0,  0,
		 -5,  0,  0,  0,  0,  0,  0, -5,
		 -5,  0,  0,  0,  0,  0,  0, -5,
		 -5,  0,  0,  0,  0,  0,  0, -5,
		 -5,  0,  0,  0,  0,  0,  0, -5,
		 -5,  0,  0,  0,  0,  0,  0, -5,
		  5, 10, 10, 10, 10, 10, 10,  5,
		  0,  0,  0,  0,  0,  0,  0,  0
	};
};