#pragma once
#include "Piece.h"

class Queen : public Piece {
public:
	Queen(int x, int y, const std::string spritename,bool white, Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
	virtual void GetTargets(Map* oppoPieces)override;
	virtual int GetScore();
private:
	int score = 900;
};