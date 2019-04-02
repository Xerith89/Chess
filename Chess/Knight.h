#pragma once
#include "Piece.h"

class Knight : public Piece {
public:
	Knight(int x, int y, const std::string spritename, bool white, const Board& brd);
	virtual std::vector<std::pair<Coords, Coords>> GetMoves()override;
	virtual std::vector<std::pair<Coords, Coords>> GetCheckedMoves()override;
private:
};