#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(int x, int y, const std::string spritename, bool white, Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
private:
};