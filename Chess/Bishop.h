#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop(int x, int y, const std::string spritename, bool white,Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
private:
};